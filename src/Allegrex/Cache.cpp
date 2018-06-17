#include "Cache.h"
#include <cmath>

#include "COP0.h"
#include <iostream>
#include <iomanip>

//TODO: Implement instruction cache.
/*
 * Constructor initializing the cache sizes
 */
Cache::Cache(PSP *bus, COP0 &systemCoprocessor)
:BusDevice(bus)
,iCache(lineCount)
,dCache(lineCount)
,systemCoprocessor(systemCoprocessor)
{
}

/*

 */
void Cache::CacheOp(uint32 op, uint32 vAddr, uint32 pAddr){
	using namespace std;

	/* Dump operatoinal imformation
	cout << "cache operation: " << dec <<  op\
	     << " vAddr: 0x" << hex << setw(8) << setfill('0') << vAddr\
		 << " pAddr: 0x" << hex << setw(8) << setfill('0') << pAddr\
		 << endl;
	// */

	unsigned int cacheCode = op & 0x03;
	// cout << "cache code: " << cacheCode << endl;
	static const char *affectedCacheName[4] = {
		"primary instruction",
		"primary data",
		"secondary instruction",
		"secondary data (or combined instruction/data)"
	};

	// cout << "affected cache: " << affectedCacheName[cacheCode] << endl;

	unsigned int operationCode = op >> 2;
	// cout << "operation: " << operationCode << endl;
	

	bool implemented = false;
	string description="Invalid Operation";

	// On full implementation of the cache, no operation should be skipped
	// rendering this variable and the corresponding logic obsolete.
	// TODO: fill implementation of the cache operations.
	bool skipped = false;

	//enumerations to make the code more readable.
	// TODO: not sure if allegrex follows the MIPS documentation on those operations. Just a note for the future!
	auto target = static_cast<CacheType>(cacheCode);
	switch(operationCode){
	case 0:
		switch(target){
		case Instruction:
			description = "Index Invalidate";
			indexInvalidate(vAddr, target);
			break;
		case Secondary_Instruction:
			description = "Index Invalidate";
			// not implemented
			// Allegrex has no secondary cache.
			break;
		case Data:
		case Secondary_Data:
			description = "Index Writeback Invalidate";
			break;
		}
		break;
	
	case 1:
		description = "Index Load Tag";
		indexLoadTag(vAddr, target);
		skipped = true;
		break;
	
	case 2:
		description = "Index Store Tag";
		break;
	
	case 3:
		switch(target){
			case Secondary_Data:
			case Data:
				description = "Create dirty exclusive";
				break;
			case Instruction:
			case Secondary_Instruction:
				//invalid operation
				break;
		}
		break;

	case 4:
		description = "Hit Invalidate";
		switch(target){
			case Instruction:
				implemented = true;
				hitInvalidate(vAddr, pAddr, Instruction);
				break;
			case Data:
				implemented = true;
				hitInvalidate(vAddr, pAddr, Data);
				break;
			case Secondary_Instruction:
			case Secondary_Data:
				break;
		}
		break;

	case 5:
		switch(target){
			case Data:
			case Secondary_Data:
				description = "Hit Writeback Invalidate";
				break;
			case Instruction:
				description = "Fill";
				break;
			case Secondary_Instruction:
				// Invalid operation
				// optional
				break;
		}
		break;
	
	case 6:
		switch(target){
			case Data:
			case Secondary_Data: // Optional
			case Secondary_Instruction: //Optional
				description = "Hit Writeback";
				break;
			case Instruction:
				// Invalid operation
				break;
		}
		break;
	
	case 7:
		switch(target){
			case Secondary_Instruction:
			case Secondary_Data:
				description = "Hit Set Virtual";
				break;
			case Instruction:
			case Data:
				// TODO: Fetch and lock maybe
				// Invalid operation for now
				break;
		}
		break;
	}

	if(skipped){
		cout << "Cache: Skipped " << description << " on "
		     << affectedCacheName[target] << " cache." << endl;
	}
	else if(!implemented){
		throw runtime_error(
			"Cache::CacheOp: Unimplemented cache operation: " + description +
			" on " + affectedCacheName[target] + " cache."
		);
	}
		
}

uint32 Cache::lineIndex(uint32 vAddr){
	const uint32 VABits = ceil(log(cacheSize));
	const uint32 index = (vAddr & ((1 << VABits) -1) >> n);
	return index;
}

// Instruction cache operations
/*
 * Get the inctruction cache line that corresponds to the specified vAddr.
 */
Cache::ILine& Cache::getILine(uint32 vAddr){
	return iCache.at(lineIndex(vAddr));
}

/*
 * Read from the instruction cache.
 * 
 */
uint32 Cache::iRead(uint32 vAddr, uint32 pAddr){
	throw std::runtime_error("YAY!!! let's check the instruction cache!!");

	std::cout << "Reading ffrom instruction cache for 0x"
	          << std::hex << vAddr << std::endl;
	auto line = getILine(vAddr);

	if(line.tag.PTag != (pAddr>>11)){
		throw std::runtime_error("Instruction cache miss");
	}


	// TODO: make it better and check correctness.
	// primary cache hit
	//make a mask where the lowest n bits are 1
	const uint32 mask =(1<<n) -1;
	const uint32 lowBits = vAddr & mask;
	const uint32 pathSelector = lowBits >> 3;
	const uint32 wordSelector = lowBits >> (n-1);

	return line.data[pathSelector].words[wordSelector];
}

/*
 * Returns a filled data cache line based on a physical address.
 */
//TODO: abstract this to a common function merging dGetLIne
//TODO: Ultimately move bus handling to a more appropriate place.
Cache::ILine Cache::iGetLine(uint32 pAddr){
	uint32 mask = ~((1 << n) - 1);
	uint32 baseAddr = pAddr & mask;

	ILine tempLine;
	
	//for all the words in the line
	for(auto &path: tempLine.data){
		for(auto &word: path.words){
			//request the appropriate word from the main memory
			const BusDevice::Request r = {
				BusDevice::devCPUCACHE,
				BusDevice::devMainMemory,
				BusDevice::Read,
				baseAddr,
				0
			};

			//set the data pending flag and request the data
			dataPending = true;
			sendRequest(r);

			//wait for the data to be received
			while(dataPending){
				// wait
			}

			//and save then in the line
			word = receivedData;
			
			//bump the address for the next read
			baseAddr += 4;
		}
	}
	
	tempLine.tag = {
		pAddr >> 12,
		1, // set the currently loaded line as a valid one
		1  // unused even parity
	};
	
	return tempLine;
}

// Data cache operations
Cache::DLine& Cache::getDLine(uint32 vAddr){
	/*
	size_t VAbits = ceil(log(cacheSize));
	//get the cache line index
	//uint32 index = (vAddr & ((1<<14)-1)) >> 5;
	// make ti all f where needed and shift it to get the index
	uint32 index = (vAddr & ((1<<VAbits)-1)) >> n;
	*/
	return dCache.at(lineIndex(vAddr));
}



/*
 * Read data from the cache. Handle cache miss.
 */
uint32 Cache::dRead(uint32 vAddr, uint32 pAddr){
	auto &line = getDLine(vAddr);

	// check the tag
	// keep bits 31-12
	if(line.tag.PTag != (pAddr >> 11)){
		//miss
		//save the line if dirty
		if(line.tag.W)
			dSaveLine(pAddr, line);
		//reload the line from the memory
		line = dGetLine(pAddr);

		std::cerr << "Cache miss" << std::endl;
	}
		
	
	switch(line.tag.CS){
	case 0: // Invalid
	/* A cache line that does not contain valid information must be marked
	 * invalid, and cannot be used. For example, a cache line is marked invalid
	 * if the same information, located in another cache, is modified. A cache
	 * line in any other state than invalid is assumed to contain valid
	 * information.
	 */
		// Cache miss. Reload line from memory.
		std::cout << "Cache invalid miss" << std::endl;
		line = dGetLine(pAddr);
		break;
	case 1: //shared
	/* A cache line that is present in more than one cache in the system is
	 * shared.
	 */
		break;
	case 2: // clean exclusive
	/* A clean exclusive cache line contains valid information and this cache
	 * line is not present in any other cache. The cache line is consistent
	 * with memory and is not owned by the processor.
	 */
		break;
	case 3: // dirty exclusive
	/* A diry exclusive cache line contains valid information and is not
	 * present in any oher cache. The cahce line is inconsistent with memory
	 * and is owned by the processot (see Cache line ownership).
	 */
		break;
	}



	// TODO: make it better and check correctness.
	// primary cache hit
	//make a mask where the lowest n bits are 1
	const uint32 mask =(1<<n) -1;
	const uint32 lowBits = vAddr & mask;
	const uint32 pathSelector = lowBits >> 3;
	const uint32 wordSelector = lowBits >> (n-1);

	return line.data[pathSelector].words[wordSelector];
}

/*
 * Returns a filled data cache line based on a physical address.
 */
Cache::DLine Cache::dGetLine(uint32 pAddr){
	uint32 mask = ~((1 << n) - 1);
	uint32 baseAddr = pAddr & mask;

	DLine tempLine;
	
	//for all the words in the line
	for(auto &path: tempLine.data){
		for(auto &word: path.words){
			//request the appropriate word from the main memory
			const BusDevice::Request r = {
				BusDevice::devCPUCACHE,
				BusDevice::devMainMemory,
				BusDevice::Read,
				baseAddr,
				0
			};

			//set the data pending flag and request the data
			dataPending = true;
			sendRequest(r);

			//wait for the data to be received
			while(dataPending){
				// wait
			}

			//and save then in the line
			word = receivedData;
			
			//bump the address for the next read
			baseAddr += 4;
		}
	}
	
	tempLine.tag = {
		pAddr >> 12,
		2, // clean exclusive
		0, // unused parity bit
		0, // line hasn't been written
		1  // unused even parity for the w bit
	};
	
	return tempLine;
}


/*
 * Saves a cache line to the main memory.
 */
void Cache::dSaveLine(uint32 pAddr, Cache::DLine &line){
	//mask out the low n bits
	uint32 mask = ~((1 << n)-1);
	uint32 baseAddr = pAddr & mask;

	// for al the data paths in the cache line
	for(auto path: line.data){
		// for all the words in a data path
		for(auto word: path.words){
			// push them in the main memory.
			const BusDevice::Request r = {
				BusDevice::devCPUCACHE,
				BusDevice::devMainMemory,
				BusDevice::Write,
				baseAddr,
				word
			};

			sendRequest(r);

			baseAddr += 4;
		}
	}
}


void Cache::serviceRequest(const struct BusDevice::Request &req){
	switch(req.function){

		case BusDevice::Reply:
			if(dataPending){
				receivedData = req.param1;
				dataPending = false;
			}
			break;

		case BusDevice::Read:
		case BusDevice::Write:
		case BusDevice::Reset:
		default:
			throw std::logic_error("Cache: function not recognised");
	}
}

/* Set the state of the cache block at the specified index to invalid.
 *
 * This required encoding may be used by software to invalidate the entire
 * instruction cache by stepping through all valid indices.
 *
 * (The index is calculated using the vAddr).
 */
void Cache::indexInvalidate(uint32 vAddr, CacheType target){
	if(not(target == Instruction))
		throw std::runtime_error("Cache: Index invalidate is implemented only for the primary instruction cache");
	// Gets the line and sets its the valid bit to false.
	getILine(vAddr).tag.V = false;
}


/* Read the tag for the cache block at the specified index and place it into
 * the TagLo and TagHi CP0 registers, ignoring any ECC or parity errors.
 * Also load the data ECC or parity bits into the ECC register.
 */
void Cache::indexLoadTag(uint32 vAddr, CacheType target){
	if(target == Data){
		//get the tag
		auto tag = getDLine(vAddr).tag;

		// construct the coprocessor register
		COP0::PTagLoRegister coptag;
		coptag.P = tag.P;
		coptag.PState = tag.CS;
		coptag.PTagLo = tag.PTag;

		// set the coprocesor register
		systemCoprocessor.ptagLoReg = coptag;
	}
	else if(target == Instruction){
		auto tag = getILine(vAddr).tag;
		COP0::PTagLoRegister coptag;
		coptag.P = tag.P;
		coptag.PState = tag.V;
		coptag.PTagLo = tag.PTag;

		systemCoprocessor.ptagLoReg = coptag;
	}
	else{
		//throw std::runtime_error("Cache: index load tag is implemented only for primary data.");
	}
}

/*
 * If the cache block contains the specified address, mark the cache block
 * invalid.
 */
void Cache::hitInvalidate(uint32 vAddr, uint32 pAddr, CacheType target){
	if(target == Data){
		// ret the cache line
		auto line = getDLine(vAddr);
		// if the line references the same physical address
		if((pAddr >> 12) == line.tag.PTag){
			// set the state of the line to invalid
			line.tag.CS = 0;
		}
	}
	else if(target == Instruction){
		auto line = getILine(vAddr);
		if((pAddr >> 12) == line.tag.PTag){
			line.tag.V = false;
		}
	}
	else{
		throw std::runtime_error("Cahce: Unimplemented hit invalidate on secondary cahe");
	}

}
