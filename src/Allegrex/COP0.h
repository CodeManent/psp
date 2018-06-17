#ifndef COP0_H_
#define COP0_H_
#pragma once

#include "Coprocessor.h"
#include "../BusDevice.h"
#include "Cache.h"

class COP0: public Coprocessor, public BusDevice
{
	//instructions that need access
	friend class ERET;
	friend class CACHE;

	//classes that need accsess
	friend class Cache;

	// *****THERE IS NO TLB IN ALLEGREX*****

	// two helping vars to handle the branching instructions
	uint32 jumpTarget;
	uint32 delaySlot;
	bool LLbit;
	Cache cache;

public:
	struct IndexRegister;
	struct RandomRegister;
	struct EntryLoRegister;
	struct ContextRegister;
	struct PageMaskRegister;
	struct WiredRegister;
	struct EntryHiRegister;
	struct StatusRegister;
	struct CauseRegister;
	struct PRidRegister;
	struct ConfigRegister;
	struct WatchLoRegister;
	struct WatchHiRegister;
	struct XContentRegister;
	struct ECCRegister;
	struct CacheErrRegister;
	struct PTagLoRegister;
	struct STagLoRegister;

private:
	IndexRegister    &indexReg;
	RandomRegister   &randomReg;
	EntryLoRegister  &entryLo0Reg;
	EntryLoRegister  &entryLo1Reg;
	ContextRegister  &contextReg;
	PageMaskRegister &pageMaskReg;
	WiredRegister    &wiredReg;
	EntryHiRegister  &entryHiReg;
	StatusRegister   &statusReg;
	CauseRegister    &causeReg;
	PRidRegister     &pridReg;
	ConfigRegister   &configReg;
	WatchLoRegister  &watchLoReg;
	WatchHiRegister  &watchHiReg;
	XContentRegister &xContentReg;
	CacheErrRegister &cacheErrReg;
	PTagLoRegister   &ptagLoReg;
	STagLoRegister   &stagLoReg;

public:

	enum RegNames{
		Index = 0,
		Random = 1,
		EntryLo0 = 2,
		EntryLo1 = 3,
		Context=4,
		PageMask = 5,
		Wired = 6,

		BadVAddr = 8,
		Count = 9,
		EntryHi = 10,
		Compare = 11,
		Status = 12,
		Cause = 13,
		EPC = 14,		//Exception Program Counter
		PRid = 15,
		Config = 16,
		LLAddr = 17,
		WatchLo = 18,
		WatchHi = 19,
		XContext = 20,

		ECC = 26,
		CacheErr = 27,
		TagLo = 28,
		TagHi = 29,
		ErrorEPC = 30
	};

	enum ExceptionCode{
		Int = 0,	//Interrupt
		Mod = 1,	//TLB modification
		TLBL = 2,	//TLB exception (load or instructino fetch)
		TLBS = 3,	//TLB exception (store)
		AdEL = 4,	//Address Error exception (load or instructino fetch)
		AdES = 5,	//Address error exception (store)
		IBE = 6,	//Bus error exception (instruction fetch)
		DBE = 7,	//Bus error exception (data reference:load or store)
		SYS = 8,	//Syscall exception
		Bp = 9,		//Breakpoint
		RI = 10,	//Reserved exception
		CpU = 11,	//Coprocessor usable exception
		Ov = 12,	//Arithmetic overflow exception
		Tr = 13,	//Trap exception
		VCEI = 14,	//Virtual coherency Exception instruction
		FPE = 15,	//Floating-Point exception
		/* 16 - 22 RESERVED */
		WATCH = 23,	//Reference to WatchHi/WatchLo address
		/* 24 - 30 RESERVED */
		VCED = 31,	//Virual Coherency Exception data

		// use reserved space for caceh and NMI exceptions
		CacheCode = 24,
		NMICode = 25
	};
	



	COP0(Allegrex &al, PSP *bus);
	virtual ~COP0(void);

	long step();
	void reset();				//Reset Exception Processing
	void cacheError();			//Cache Error Exception Processing
	void NMI();					//Soft Reset and NMI Exception Processing
	void generalException();	//General Exception Processing (Except Reset, Soft Reset, NMI, and Cache Error)
	void raiseException(const ExceptionCode code);
	void verifyCoprocessorUsability(unsigned int COPnum);


	enum Segment{
		useg,	//0x00000000 - 0x80000000
		kseg0,	//0x80000000 - 0xA0000000
		kseg1,	//0xA0000000 - 0xC0000000
		sseg,	//0xC0000000 - 0xE0000000
		kseg3	//0xE0000000 - 0xFFFFFFFF
	};

	Segment getSegment(const uint32 vAddr) const;
	bool validateAddress(const uint32 vAddr) const;

	uint32 addressTranslation(const uint32 vAddr, bool &cachable) const;

	enum LoadType{INST, DATA};
	uint32 loadMemory32(const uint32 vAddr, LoadType role = DATA);
	void writeMemory(const uint32 vAddr, const uint32 data);

	uint32 receivedData;
	bool dataPending;

	void jump(const uint32 target, const bool likely);

	void receiveData(uint32 data);
	virtual void serviceRequest(const struct BusDevice::Request &req);

/************************************************************************** p.85
 * NOT USED because allegrex has no TBL
 *
 * The Index register (0) is a 32-bit, read/write register containing six bits
 * to index an entry in the TLB.
 *     - p: Success or failure of a TLB Probe (TLBP) instruction
 *     - index: Specifies the TLB entry affected by TLB Read (TLBR) or
 *              TLB Write (TLBWI) instructions.
 */
struct IndexRegister{
	uint index:6;		//tlb entry affected
	uint reserved:25;
	uint P:1;			//1 when previous TLBP instruction was unsuccessful
};

/************************************************************************** p.86
 * NOT USED because allegrex has no TBL
 *
 * The Random register (1) is a read-only reg of which 6 bits index an entry in
 * the TLB. This reg decrements as each instruction executes.
 *     - random: TLB Random index.
 *     - reserved: Must be written as zeros and returns 0 when read.
 */
struct RandomRegister{
	uint random:6;		// TLB Random index
	uint reserved:26;
};


/************************************************************************** p.87
 * NOT USED because allegrex has no TBL
 *
 * The EntryLo register consists if two registers that have identical formats:
 *   - EntryLo0 (2) is used for even virtual pages.
 *   - EntryLo1 (3) is used for odd virtual pages.
 *
 * The EntryLo regs are read/write. They hold the physical page frame number (PFN)
 * of the TLB entry for even and odd pages, respectively, when performing TLB
 * read and write operations.
 *
 *     - PFN: Page frame number; the upper bits of the physical address.
 *     - C: Specifies the TLB page coherency attribute.
 *     - D: Ditry. If this bit is set, the page is marked as dirty and, therefore
 *          writable. This bit is actually a write-protect bit that software can
 *          use to prevent alteration of data.
 *     - V: Valid. If this bit is set, it indicates that the TLB entry is valid;
 *          otherwise a TLBL or TLBS miss occurs.
 *     - G: Global. If this bit is set in both Lo0 and LO1, then the processor
 *          ignores the ASID during TLB lookup.
 *     - Reserved: Must be written woth 0 and return 0 when read.
 */
struct EntryLoRegister{
	uint G: 1;
	uint V: 1;
	uint D: 1;
	uint C: 3;
	uint PFN: 24;
	uint reserved: 2;
};

/************************************************************************ p.102
* NOT USED because allegrex has no TBL
 *
 * Context register (4) is a read/write reg containing the pointer to the page
 * table entry (PTE) array. 
 *
 *     - BaddVPN2: This field is written by hardware on a miss. It contains
 *                 the virtual page number (VPN) of the most recent virtual
 *                 address that did not have a valod translation.
 *     - PTEBase: This field id a read/write field for use by the operating
 *                system. It is normally written with a value that allows
 *                the operating system to use the Context reg as a pointer
 *                into the current PTE array in memory.
 */
struct ContextRegister{
	uint reserved:4;
	uint BadVPN2:19;
	uint PTEBase:9;
};


/************************************************************************** p.87
 * NOT USED because allegrex has no TBL
 *
 * The PageMask register (5) is a read/write reg used for reading from or
 * writting to the TLB; it holds a comparison mask that sets the variable page
 * size for each TLB entry.
 *
 *     -mask: Page comparison mask.
 *
 */
struct PageMaskRegister{
	uint reserved0 : 13;
	uint mask : 12;
	uint reserved1: 7;
};

 
/************************************************************************** p.88
 * NOT USED because allegrex has no TBL
 *
 * The Wired (6) reg is a read/write reg that specifies the boundry between the
 * wired and random entries of the TLB.
 *
 *     - wired: TLB Wired boundry.
 *
 */ 
struct WiredRegister{
	uint wired:6;
	uint reserved:26;
};


/************************************************************************ p.103
 * NOT USED because allegrex has no TBL
 *
 * Bad Virtual address Register (BadVAddr) (8)
 *
 * It is a read-only reg that displays the most recent virtual address that
 * caused one of the following exceptions:
 *     - TLB Invalid
 *     - TLB Modified
 *     - TLB Refill
 *     - Virtual Coherency Data Access
 *     - Virtual Coherency Instruction Access
 */

/************************************************************************ p.103
 *
 * Count Register (9)
 *
 * It acts as a timer, incrementing at a constant rate -- half the maximum
 * instruction issue rate -- whether or not an instruction is executed, retired
 * or any forward progress is made through the pipeline.
 *
 * This register can be read or written. It can be written for diagnostic
 * purposes or system initialization; for example, to synchronize processors.
 */


/************************************************************************** p.89
 * NOT USED because allegrex has no TBL
 *
 * The EntryHi (10) reg holds the high-order bits of a TLB entry for TLB read
 * and write operations.
 *
 * The EntryHi reg is accessed by the TLB Probe, TLB Write Random,
 * TLB Write Indexed and TLB Read Indexed instructions.
 *
 *     - VPN2: Virtual page number divided by two (maps two pages).
 *     - ASID: Address space ID field. An 8-bit field that lets multiple
 *             processes share the TLB; each process has a distinct mapping of
 *             the otherwise identical virtual page numbers.
 *
 */ 
struct EntryHiRegister{
	uint8 ASID;
	uint reserved: 5;
	uint VPN2: 19;
};

/************************************************************************ p.103
 *
 * Compare Register (11)
 *
 * It acts as a timer (see also counter register); it maintains a stable value
 * that does not change on its own.
 *
 * When the value of the Count reg equals the value of the Compare reg,
 * interrupt bit IP(17) in the cause reg is set. This causes an interrupt as
 * soon as the interrupt is enabled.Writing a value to the Compare reg, as a
 * side effect clears the timer interrupt.
 *
 * For diagnostic purposes, the Compare reg is read/write. In normal use however
 * the compare reg is write only.
 */

/*******************************************************************************
 *
 * Status register (12)
 */
struct StatusRegister{
	uint IE:1;		//Interrupt Enable (0=disable 1=enable)
	uint EXL:1;		//Exception Level (0=normal 1=error)
	uint ERL:1;		//Error Level (0=normal 1=error)
	uint KSU:2;		//Mode bits (10=user 01=Supervisor 00=Kernel)
	uint UX:1;		//for tlb
	uint SX:1;		//for tlb
	uint KX:1;		//for tlb
	uint IM:8;		//Interrupt mask
	//uint DS:9;	//Diagnostic Status field
	uint DSDE:1;	//Parity or ECC errors cannot cause exceptions
	                // 0: parity/ecc remain enabled
					// 1: disables parity/ECC
	uint DSCE:1;	//about the ECC register
	uint DSCH:1;	//Cache hit/miss indication
					// 0: miss
					// 1: hit
	uint DSreserved0:1;
	uint DSSR:1;	//1=Reset* signal or NMI has caused a soft reset exception
	uint DSTS:1;	//1=TLB shutdown has occurred (read only)
	uint DSBEV:1;	//TLB refill and general exception vectors
	                // 0: normal
					// 1: bootstrap
	uint DSreserved:2;
	uint RE:1;		//Reverse endian bit, valid in user mode		
	uint FR:1;		//Floating point registers (0=16regs 1=32regs)
	uint RP:1;		//Reduced power (0=full speed 1=reduced clock)
	//uint CU:4;
	uint CU0:1;		//Coprocessor 0 Usability
	uint CU1:1;		//Coprocessor 1 Usability
	uint CU2:1;		//Coprocessor 2 Usability
	uint CU3:1;		//Coprocessor 3 Usability
};

struct CauseRegister{
	uint reserved0:2;
	uint ExcCode:5;	//Exception code
	uint reserved1:1;
	uint IP:8;		//Interrupt pending
	uint reserved2:12;
	uint CE:2;		//CoProcessor number on coProcessor unusable exception
	uint reserved3:1;
	uint BD:1;		//Last exception was on branch delay slot (0=no 1=yes)
};

/************************************************************************** p.89
 *
 * Processor Revision Identifier (PRId) reg (15)
 * A read-only reg which contains information identifying the implementation and
 * revision level of the CPU and CPU0.
 *
 *     - Imp: Implementation number (0x04 for R4000).
 *     - Rev: Revision number (in major.minor format):
 *         - 7..4: major revision number.
 *         - 3..0: minor revision number.
 */
struct PRidRegister{
	uint rev:8;			//Revision Number
	uint imp:8;			//Implementation Number
	uint reserved:16;
};

/************************************************************************** p.90
 *
 * The Config (16) reg specifies various configuration options selected on R4000
 * processors.
 */
struct ConfigRegister{
	uint KO:3;		//kseg0 coherency algorithm
	                // (see EntryLo regs and the C field)
	
	uint CU:1;		//Update on Store Conditional (SC)
	                // 0: SC uses coherency algorithm specified by TLB
	                // 1: SC uses cachable coherent update on write
	                
	uint DB:1;		//Primary Dcache line size
	                // 0: 16 bytes
	                // 1: 32 bytes
	
	uint IB:1;		//Primary Icache line size
	                // 0: 16 bytes
	                // 1: 32 bytes
	
	uint DC:3;		//Primary Dcache size = 2^(12+DC) bytes. In the R4000 this
	                // is set to 8Kbytes, in R4400 this is set to 16Kbytes.
	                
	uint IC:3;		//Primary Icache size = 2^(12+IC) bytes. In the R4000 this
	                // is set to 8Kbytes, in R4400 this is set to 16Kbytes.
	                
	uint reserved:1;
	uint EB:1;		//Block ordering
	                // 0:sequential
	                // 1:sub-block
	                
	uint EM:1;		//ECC mode enable
	                // 0: ECC mode enabled
	                // 1: Parity mode emabled
	
	uint BE:1;		//BigEndianMem
	                // 0: kernel and memory are little endian
	                // 1: kenrel and memory are big endian
	                
	uint SM:1;		//Dirty shared coherent state
	                // 0: Dirty Shared Coherency state is enabled
	                // 1: Dirty shared state is disabled
	                
	uint SC:1;		//Secondary Cace present
	                // 0: S-Cache present
	                // 1: no S-cache present
	                
	uint EW:2;		//System port width
	                // 0: 64 bits
	                // 2.3.4: Reserved
	                
	uint SW:1;		//Secondary cache port width
	                // 0: 128-bit data path to S-Cache
	                // 1: Reserved
	                
	uint SS:1;		//Split secondary cache mode
	                // 0: Instruction and data mixed in secondary cache (joint cache)
	                // 1: Instruction and data separated by SCAddr(17)
	                
	uint SB:2;		//Secondary cache line size
	                // 0: 4 words
	                // 1: 8 words
	                // 2: 16 words
	                // 3: 32 words
	                
	uint EP:4;		//Transmit data pattern (pattern for write-back data)
	                // 0: D        Doubleword every cycle
	                // 1: DDx      2 Doublewords every 3 cycles
	                // 2: DDxx     2 Doublewords every 4 cycles
	                // 3: DxDx
	                // 4: DDxxx
	                // 5: DDxxxx
	                // 6: DxxDxx
	                // 7: DDxxxxxx
	                // 8: DxxxDxxx
	                
	uint EC:3;		//System clock ratio
	                // 0: processor clock divided by 2
	                // 1: processor clock divided by 3
	                // 2: processor clock divided by 4
	                // 3: processor clock divided by 6 (R4400 only)
	                // 4: processor clock divided by 8 (R4400 only)
	uint CM:1;		//Master-Checker Mode
	                // 1: Master/checker mode enabled
};

/************************************************************************** p.93
 *
 * The Load Linked Address (LLAddr) register (174) is a read/write register
 * that contains the physical address read by the modt Load Linked instruction.
 *
 * The register is for diagnostic purposes only and serves no function during
 * normal operation.
 *
 * The register contains the the bits 35...4 of the physical address.
 */

struct WatchLoRegister{
	uint W:1;		//1 = Trap on store references
	uint R:1;		//1 = Trap on load references
	uint reserved:1;
	uint PAddr0:29;	//Bits 31:3 of the physical address
};

struct WatchHiRegister{
	uint PAddr1:4;	//Bits 35:32 of the physicak address
	uint reserved:28;
};

struct XContentRegister{
	uint reserved:4;
	uint BadVPN2:27;
	uint R:2;
	uint PTEBase:31;
};

struct ECCRegister{
	uint ECC:8;
	uint reserved:24;
};

struct CacheErrRegister{
	uint PIDx:3;//Bits vAddr(14:12) of the doubleword in error (used with SIdx to construct a virtual index for the primary caches
	uint SIDx:19;//Bits pAddr(21:3) of the reference that encountered the error
	uint reserved;
	uint EW:1;	//Only available on 4400
	uint EI:1;	//This bit is set on a secondary data cache ECC error while refilling the primary cache on a store miss.  The ECC handler must first do an Index Store Tag to invalidate the incorrect data from the primary data cache.
	uint EB:1;	//Set if a data error occurred in addition to the instruction error (indicated by the remainder of the bits). If so, this requires flushing the data cache after fixing the instruction error
	uint EE:1;	//=1 Error occurred on the SysAD bus
	uint ES:1;	//0=internal reference 1=external reference
	uint ET:1;	//Tag field error occurred (0=no 1=yes)
	uint ED:1;	//Data field error occurred (0=no 1=yes)
	uint EC:1;	//Cache level of the error (0=primary 1=secondary)
	uint ER:1;	//Type of reference (0=instruction 1=data)
};

/************************************************************************** p.93
 * Cache Tag Registers [TagLo (28) and TagHi (29)]
 *
 * The TagLo and TagHi regs are 32bit read/write regs that hold either the
 * primary cache tag and parity or the secondary cache tag and ECC during cache
 * initialization, cache diagnostics or cache error processing. The Tag regs
 * are wirtten by the Cache and MTC0 instructions.
 *
 *     - PTagLo: Physical address bits 35:12
 *     - PState: Primary cache state
 *     - P: Primaty tag even parity bit
 *
 *     - STagLo: physical address bits 35:17
 *     - SState: Secondary cache state
 *     - VIndex: Virtual index of the associated Primary cache line, vAddr(14:12)
 *     - ECCL ECC for the STag, SState and VIndex fields
 *
 *     The HiTag reg should not be used
 */

struct PTagLoRegister{
	uint P:1;		//primary tag even parity bit
	uint reserved:5;
	uint PState:2;	//primary cache state
	uint PTagLo:24;	//Physical address bits 35:12
};

struct STagLoRegister{
	uint ECC:7;		//ECC for the stag, SState and VIndex fields
	uint VIndex:3;	//Virtual index of associated Primary cache line vAddr(14:12)
	uint SState:3;	//secondary cache state
	uint STagLo:19;	//Physical address bits 35:17
};

};

#endif
