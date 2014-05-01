#ifndef ALLEGREX_CACHE_H
#define ALLEGREX_CACHE_H

#include <vector>
#include <stdexcept>
#include "../IntTypes.h"
#include "../BusDevice.h"

class COP0;

/*
 * The R4400 primary caches are fixed at 16 kbytes
Notes:
	A cache line is represented by a tag.
	A cache line can be either 4 or 8 words in length (set in the config reg).
 */
class Cache: public BusDevice{
	//Cahce configuration varables.
	// Each cache has its own 64bit data path.
	static const unsigned int dataPath = 8; // in bytes
	//Allegrex has a 2-way associative 32K cache (16K for data & 16K for instr).
	static const unsigned int cacheSize = 16*1024; // in bytes
	// Cache line size in words.
	static const unsigned int lineSize = 4;	// in words (32bit/4bytes per word)
	static const unsigned int lineCount = cacheSize/(4*lineSize);
	// =4 because cache line = 32 bytes
	static const int n = 4;
	
	// Structs used to emulate cache operation.
	// Parity fields remain unused for now.

	//The cache-tag for the instruction cache
	struct ITagLine{
		unsigned int PTag:24; // Physical tag (bits 31-12 of the physical addr)
		unsigned int V:1;     // Valid bit
		unsigned int P:1;     // Even parity for PTag and V fields
	};

	// the tag line for the data cache
	struct DTagLine{
		unsigned int PTag:24; // Physical tag (bits 31-12 of the pysical addr)
		unsigned int CS:2;    // Primary cache state
		                      // 0: Invalid in all R4000 configurations
							  // 1: Shared(either clean or dirty) for R4000MC
							  // 2: Clean exclusive in R4000SC and MC
							  // 3: Dirty exclusive in all R4000 configs
		unsigned int P:1;     // Even parity for the PTag and CS fields
		unsigned int W:1;     // Write-back bit (set if cache line has been written)
		unsigned int WP:1;    // Even parity for the write-back bit
	};
	
	// Struct holding the actual data of the cache line
//	unsigned int Data;    // Even parity; 1 parity bit per byte of data
	union DataLine{
		unsigned char bytes[dataPath];
		uint32 words[dataPath/sizeof(uint32)];
	};

	// Struct modeling the instruction cache line.
	struct ILine{
		ITagLine tag;
		DataLine data[4*lineSize/dataPath];
	};

	// Struct modeling the data cache line.
	struct DLine{
		DTagLine tag;
		DataLine data[4*lineSize/dataPath];
	};

	// The actual containers for the data and instruction caches. Their sizes
	// are set during the Cache class constructor.
	std::vector<ILine> iCache;
	std::vector<DLine> dCache;

	//reference to the current system cooprocessor
	COP0 &systemCoprocessor;

	bool dataPending;
	uint32 receivedData;

public:
	Cache(PSP *bus, COP0 &systemCoprocessor);
	void CacheOp(uint32 op, uint32 vAddr, uint32 pAddr);
	enum CacheType {Instruction=0, Data=1, Secondary_Instruction=2, Secondary_Data=3};

	static uint32 lineIndex(uint32 pAddr);

	//TODO: remove unused parameted (pAddr for now)
	//Instruction cache operations
	ILine& getILine(uint32 vAddr, uint32 pAddr);
	uint32 iRead(uint32 vAddr, uint32 pAddr);
	ILine iGetLine(uint32 pAddr);
	//Data cache operations
	DLine& getDLine(uint32 vAddr, uint32 pAddr);
	uint32 dRead(uint32 vAddr, uint32 pAddr);
	DLine dGetLine(uint32 pAddr);
	void dSaveLine(uint32 pAddr, DLine &line);
	
	virtual void serviceRequest(const struct BusDevice::Request &req);
	
	void indexInvalidate(uint32 vAddr, uint32 pAddr, CacheType target);
	void indexWritebackInvalidate(uint32 vAddr, uint32 pAddr, CacheType targ);
	void indexLoadTag(uint32 vAddr, uint32 pAddr, CacheType target);
	void indexStoreTag(uint32 vAddr, uint32 pAddr, CacheType target);
	void createDirtyExclusive(uint32 vaDDR, uint32 pAddr, CacheType target);
	
	void hitInvalidate(uint32 vAddr, uint32 pAddr, CacheType target);
	void hitWritebackInvalidate(uint32 vAddr, uint32 pAddr, CacheType target);
	void fill(uint32 vAddr, uint32 pAddr);
	void hitWriteback(uint32 vAddr, uint32 pAddr, CacheType target);
	void hitSetVirtual(uint32 vAddr, uint32 pAddr, CacheType target);
};


#endif

