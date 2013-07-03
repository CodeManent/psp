#include "COP0.h"
#include "Allegrex.h"
#include "../TODO.h"
#include "../BusDevice.h"

struct COP0::IndexRegister{
	uint index:6;		//tlb entry affected
	uint reserved:25;
	uint P:1;			//1 when previous TLBP instruction was unsuccessful
};

struct COP0::RandomRegister{
	uint random:6;		// TLB Random index
	uint reserved:26;
};

struct COP0::ContextRegister{
	uint reserved:4;
	uint BadVPN2:19;
	uint PTEBase:9;
};


struct COP0::WiredRegister{
	uint wired:6;
	uint reserved:26;
};

struct COP0::StatusRegister{
	uint IE:1;		//Interrupt Enable (0=disable 1=enable)
	uint EXL:1;		//Exception Level (0=normal 1=error)
	uint ERL:1;		//Error Level (0=normal 1=error)
	uint KSU:2;		//Mode bits (10=user 01=Supervisor 00=Kernel)
	uint UX:1;		//for tlb
	uint SX:1;		//for tlb
	uint KX:1;		//for tlb
	uint IM:8;		//Interrupt mask
	//uint DS:9;	//Diagnostic Status field
	uint DSDE:1;	//Parity or ECC errors cannot cause exceptions (0=parity/ecc remain enabled 1=disables parity/ECC)
	uint DSCE:1;	//about the ECC register
	uint DSCH:1;	//Cache hit/miss indication (0=miss 1=hit)
	uint DSreserved0:1;
	uint DSSR:1;	//1=Reset* signal or NMI has caused a soft reset exception
	uint DSTS:1;	//1=TLB shutdown has occurred (read only)
	uint DSBEV:1;	//TLB refill and general exception vectors (0=normal 1=bootstrap)
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

struct COP0::CauseRegister{
	uint reserved0:2;
	uint ExcCode:5;	//Exception code
	uint reserved1:1;
	uint IP:8;		//Interrupt pending
	uint reserved2:12;
	uint CE:2;		//CoProcessor number on coProcessor unusable exception
	uint reserved3:1;
	uint BD:1;		//Last exception was on branch delay slot (0=no 1=yes)
};

struct COP0::PRidRegister{
	uint rev:8;			//Revision Number
	uint imp:8;			//Implementation Number
	uint reserved:16;
};

struct COP0::ConfigRegister{
	uint KO:3;		//kseg0 coherency algorithm
	uint CU:1;		//Update on Store Conditional (0=use tlb 1=cachable update on write)
	uint DB:1;		//Primary Dcache line size (0=16byte 1=32byte)
	uint IB:1;		//Primary Icache line size (0=16byte 1=32byte)
	uint DC:3;		//Primary Dcache size = 2^(12+DC)
	uint IC:3;		//Primary Icache size = 2^(12+IC)
	uint reserved:1;
	uint EB:1;		//Block ordering (0=sequential 1=sub-block)
	uint EM:1;		//ECC mode enable (0=ECC mode 1=Parity mode)
	uint BE:1;		//BigEndianMem (0=big 1=little)
	uint SM:1;		//Dirty shared coherent state (0=enabled 1=disabled)
	uint SC:1;		//Secondary Cace present(0=yes 1=no)
	uint EW:2;		//System port width (=0=64bit)
	uint SW:1;		//Secondary cache port width(=0=128 bit)
	uint SS:1;		//Split secondary cache (0=no 1=yes)
	uint SB:2;		//Secondary cache line size (0=4words 1=8 2=16 3=23)
	uint EP:4;		//Transmit data pattern
	uint EC:3;		//System clock ratio
	uint CM:1;		//Master-Checker Mode
};

struct COP0::WatchLoRegister{
	uint W:1;		//1 = Trp on store references
	uint R:1;		//1 = Trap on load references
	uint reserved:1;
	uint PAddr0:29;	//Bits 31:3 of the physical address
};

struct COP0::WatchHiRegister{
	uint PAddr1:4;	//Bits 35:32 of the physicak address
	uint reserved:28;
};

struct COP0::XContentRegister{
	uint reserved:4;
	uint BadVPN2:27;
	uint R:2;
	uint PTEBase:31;
};

struct COP0::ECCRegister{
	uint ECC:8;
	uint reserved:24;
};

struct COP0::CacheErrRegister{
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

struct COP0::PTagLoRegister{
	uint P:1;		//primary tag even parity bit
	uint reserved:5;
	uint PState:2;	//primary cache state
	uint PTagLo:24;	//Physical address bits 35:12
};

struct COP0::STagLoRegister{
	uint ECC:7;		//ECC for the stag, SState and VIndex fields
	uint VIndex:3;	//Virtual index of associated Primary cache line vAddr(14:12)
	uint SState:3;	//secondary cache state
	uint STagLo:19;	//Physical address bits 35:17
};

COP0::COP0(Allegrex &al)
	:Coprocessor(al),
	indexReg(reinterpret_cast<IndexRegister &>(reg[Index])),
	randomReg(reinterpret_cast<RandomRegister &>(reg[Random])),
	contextReg(reinterpret_cast<ContextRegister &>(reg[Context])),
	wiredReg(reinterpret_cast<WiredRegister &>(reg[Wired])),
	statusReg(reinterpret_cast<StatusRegister &>(reg[Status])),
	causeReg(reinterpret_cast<CauseRegister &>(reg[Cause])),
	pridReg(reinterpret_cast<PRidRegister &>(reg[PRid])),
	configReg(reinterpret_cast<ConfigRegister &>(reg[Config])),
	watchLoReg(reinterpret_cast<WatchLoRegister &>(reg[WatchLo])),
	watchHiReg(reinterpret_cast<WatchHiRegister &>(reg[WatchHi])),
	xContentReg(reinterpret_cast<XContentRegister &>(reg[XContext])),
	cacheErrReg(reinterpret_cast<CacheErrRegister &>(reg[CacheErr])),
	ptagLoReg(reinterpret_cast<PTagLoRegister &>(reg[TagLo])),
	stagLoReg(reinterpret_cast<STagLoRegister &>(reg[TagLo]))
{
	pridReg.imp = 0x04;//R4000
	TODO("proper revision number")
	pridReg.rev = 1;//??? I just added it

	statusReg.DSTS = 0;
	statusReg.ERL = 1;
	statusReg.DSBEV =1;

	statusReg.UX = 0;	//32bit useg is selected 
}

COP0::~COP0(void)
{
}

TODO("method parameters")
void COP0::reset(){
	//reg[Random] = TLBENTRIES - 1;

	reg[Wired] = 0;
	if(causeReg.BD == 1){
		reg[ErrorEPC] = cpu.PC - 4;
	}
	else{
		reg[ErrorEPC] = cpu.PC;
	}
/*
	if(R440){
		cacheErrReg.EW = 0;
	}
*/
	statusReg.ERL = 1;
	statusReg.DSSR = 0;
	statusReg.DSTS = 0;
	statusReg.DSBEV = 1;
	//cpu.PC = 0xFFFFFFFFFBFC00000;
	cpu.PC = 0xBFC00000;
}

void COP0::cacheError(){
	if(causeReg.BD == 1){
		//if in delay slot
		reg[ErrorEPC] = cpu.PC - 4;
	}
	else{
		reg[ErrorEPC] = cpu.PC;
	}

	statusReg.EXL=1;

	if(statusReg.DSBEV == 1){
		//if bootstrap
		cpu.PC = 0xBFC00200 + 0x00000100;
	}
	else{
		cpu.PC = 0xA0000000 + 0x00000100;
	}
}

void COP0::NMI(){
	if(causeReg.BD == 1){
		//if in delay slot
		reg[ErrorEPC] = cpu.PC - 4;
	}
	else{
		reg[ErrorEPC] = cpu.PC;
	}
/*
	statusReg.ERL = 1;
	statusReg.DSSR = 1;
	statusReg.DSTS = 0;
	statusReg.DSBEV = 1;
*/
	const uint32 set  = 0x00500004;
	const uint32 mask = 0x00700004;

	reg[Status] = (reg[Status] & ~mask) | set;

	cpu.PC = 0xBFC00000;
}

void COP0::generalException(){
	uint32 vector;

	if(statusReg.EXL == 0){
		if(causeReg.BD == 1){
			//if in delay slot
			reg[EPC] = cpu.PC - 4;
		}
		else{
			reg[EPC] = cpu.PC;
		}
TODO("set cause register")
/*
		if(TLBrefill){
			vector=0x000
		}
		else if(XTLBrefill){
			vector = 0x80
		}
		else{
			//not a miss
		}
*/
		//not a miss
		vector=0x180;
	}
	else{
TODO("set cause register")
		vector=0x180;
	}

	statusReg.EXL = 1;

	if(statusReg.DSBEV == 1){
		//if bootstrap
		cpu.PC = 0xBFC00200 + vector;
	}
	else{
		cpu.PC = 0x80000000 + vector;
	}
}


COP0::Segment COP0::getSegment(const uint32 vAddr) const{
	if(vAddr < 0x80000000){
		return useg;
	}
	else if(0x80000000 <= vAddr && vAddr < 0xA0000000){
		return kseg0;
	}
	else if(0xA0000000 <= vAddr && vAddr < 0xC0000000){
		return kseg1;
	}
	else if(0xC0000000 <= vAddr && vAddr < 0xE0000000){
		return sseg;
	}
	else if(0xE0000000 <= vAddr && vAddr < 0xFFFFFFFF){
		return kseg3;
	}
	else{
		throw("Bad begment");
	}
}

bool COP0::validateAddress(const uint32 vAddr) const {

	//i don't check UX because allegrex always uses 32bits
	if(statusReg.EXL || statusReg.ERL){
		goto kernel;
	}

	switch(statusReg.KSU){
kernel:	case 0://kernel
			return true;

		case 1://supervisor
			if(0xC0000000 <= vAddr && vAddr < 0xE0000000){
				//sseg
				return true;
			}

		case 2://user
			if(vAddr < 0x80000000){
				//useg
				return true;
			}
	}

	return false;
}

uint32 COP0::addressTranslation(const uint32 vAddr, bool &cachable) const{
	cachable = true;

	Segment seg = getSegment(vAddr);

	if(!statusReg.KSU || statusReg.EXL || statusReg.ERL){
		//kernel
		switch(seg){
			case useg:
				if(!statusReg.ERL){
					cachable = false;
				}
				return vAddr;

			case kseg0:
				//cachability based on the K0 field of the status register
				return vAddr - 0x80000000;

			case kseg1:
				cachable = false;
				return vAddr - 0xA0000000;

			case sseg:
				return vAddr;

			case kseg3:
				return vAddr;

			default:
				throw("Bad segment");
		}
	}
	else{
		return vAddr;
	}
}

/*
 * Loads data by requesting them from the main memory through the main bus.
 *
 * The implementation ignores the cache for now and always loads from memory.
 */
uint32 COP0::loadMemory32(const uint32 vAddr){
//	uint32 pAddr = AddressTranslation(vAddr, DATA);
//	pAddr &= 0xfffffffC;
//	uint32 mem = loadMemory(uncached, WORD, pAddr, vAddr, DATA);
//	cpu.GPR[u.i.rt] = mem;

	if(!validateAddress(vAddr)){
		throw("Address error exception");
	}
	
	bool cachable;
	const uint32 pAddr = addressTranslation(vAddr, cachable);

	//Remove it after cache implementation
	cachable = false;

	if(cachable){
		//read from cache
		/*
		const uint32 line = (vAddr & 0x00007fe0) >> 5;
		const uint32 word = vAddr & 0x0000001f;
		dCacheLine &dcl = dCache[line];
		*/
		TODO("Finish cache implementation")
		return 0;
	}
	else{
		//read from memory
		const BusDevice::Request r = {BusDevice::devCPU, BusDevice::devMainMemory, BusDevice::Read, pAddr, 0};

		//enable the flag so to accept the data form the bus
		dataPending = true;

		cpu.sendRequest(r);
		//With the current implementation the control will return here after the data are read
		//so no wait is actually needed (but leave it because no harm is done now).

		while(dataPending){
			//wait
		}

		return receivedData;
	}
}

/*
 * Received data after they have been requested.
 * The loadMemory32 requests the data and receiveData puts them in the temporary
 * variable receivedData. When the loadMemory resumes its execution, it will use the data.
 *
 * If data were received without being requested, they are ignored.
 */
void COP0::receiveData(uint32 data){
	if(dataPending)
	{
		receivedData = data;
		dataPending = false;
	}
}

