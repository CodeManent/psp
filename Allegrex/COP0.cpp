#include "COP0.h"
#include "Allegrex.h"
#include "../BusDevice.h"
#include "UnimplementedOp.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>


COP0::COP0(Allegrex &al, PSP *bus)
	:Coprocessor(al),
	BusDevice(bus),
	jumpTarget(0),
	delaySlot(0),
	cache(bus, *this),
	indexReg(reinterpret_cast<IndexRegister &>(reg[Index])),
	randomReg(reinterpret_cast<RandomRegister &>(reg[Random])),
	entryLo0Reg(reinterpret_cast<EntryLoRegister &>(reg[EntryLo0])),
	entryLo1Reg(reinterpret_cast<EntryLoRegister &>(reg[EntryLo1])),
	contextReg(reinterpret_cast<ContextRegister &>(reg[Context])),
	pageMaskReg(reinterpret_cast<PageMaskRegister &>(reg[PageMask])),
	wiredReg(reinterpret_cast<WiredRegister &>(reg[Wired])),
	entryHiReg(reinterpret_cast<EntryHiRegister &>(reg[EntryHi])),
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
	// TODO: complete config register values
	//set the configuration information in the config register
	// configReg.K0 = ????
	// configReg.CU = ???
	configReg.DB = 1; // Primary Dcahce line size = 32 bytes
	configReg.IB = 1; // Primary ICache line size = 32 bytes
	configReg.DC = 4; // 16K DCache
	configReg.IC = 4; // 16K ICache
	// configReg.EB = ??? block orgering
	// configReg.EM = ??? ECC mode enable
	configReg.BE = 0; // Kernel and memory are little endian
	//configReg.SM = ??? dirty shared coherent state
	configReg.SC = 1; // No s-Cache present
	configReg.EW = 0; // system port width = 64 (only valid value)
	configReg.SW = 0; // 128bit data path to s-cache (only valid value)
	configReg.SS = 0; // joint s-cache
	configReg.SB = 3; // 32 words cache line for s-cache
	// configReg.EP = ???
	// configReg.EC = ???
	// configReg.CM = ???

	


	pridReg.imp = 0x04;//R4000
	// TODO: proper revision number
	pridReg.rev = 1;//??? I just added it
	pridReg.imp = 1;

	statusReg.DSTS = 0;
	statusReg.ERL = 1;
	statusReg.DSBEV =1;

	statusReg.UX = 0;	//32bit useg is selected
	statusReg.KSU = 0; // set kernel mode

	reset();
}

COP0::~COP0(void)
{
}

/*
 * Fetch the instruction from the memory[PC]
 * Execute the instruction.
 * 
 * Handle delay slot and anything other needed.
 * NOT COMPLETED
 */
long COP0::step(){
	// should increase at maximum half the instruction issue rate
	reg[Count] += 1;
	//if count reg equals compare reg
	if(reg[Compare] == reg[Count]){
		// set interrupt flag 17 in the cause reg
		causeReg.IP |= 0x10000;
	}

	// if interrupts are enabled and an unmasked interrupt is pending 
	if( statusReg.IE & statusReg.IM & causeReg.IP){
		// Raise an interrupt exception
		throw COP0::Int;
	}

	try{
		if(jumpTarget){
			if(delaySlot){
				cpu.PC = delaySlot;
				// set flag indicating we are in a delay slot
				causeReg.BD = 1;

				// we'll execute the delay slot. no other pending delay slot
				delaySlot = 0;
			}
			else{
				cpu.PC = jumpTarget;
				// clear delay slot flag
				causeReg.BD = 0;

				// branch taken, clear the var so the execution continues
				jumpTarget = 0;
			}
		}

		const uint32 inst = loadMemory32(cpu.PC, INST);
		//*
		std::cout << std::hex << std::setfill('0')
			<< "PC = 0x" << std::setw(8) << cpu.PC
			<< "\t0x" << std::setw(8) << inst
			<< '\t' << Instruction::disassemble(inst)
			<< std::endl;
		// */
		cpu.execute(inst);
		cpu.PC += 1<<2;
	}
	catch(const UnimplementedOp &uo){
		std::cerr
			// << "Unimplemented instruction"
			<< uo.dump(cpu)
			<< '\n'
			<< std::endl;

		cpu.PC += 1 << 2;
	}
	/*
	catch(const std::logic_error &le){
		std::cerr << le.what() << std::endl;
		cpu.PC += 1<<2;
	}
	catch(const std::exception &e){
		std::cerr
			<< "0x" << std::setw(8) << std::setfill('0') << std::hex << cpu.PC
			<< '\t' << e.what() << std::endl;

		throw;
	}
	catch( const char * str){
		std::cerr << "Exception: " << str << std::endl;
		cpu.PC += 1<<2;
	}
	*/
	catch(const COP0::ExceptionCode code){
		// clear jump target and delay slot vars as they will be handled by the 
		// exception handler
		jumpTarget = 0;
		delaySlot = 0;
		static int exp = 0;
		if(++exp > 5)
			throw std::runtime_error("Exception count > 5");

		std::cout << "----------------------------Handling excepion " << code << std::endl;
		//todo: handle cache exceptions and NMI
		switch(code){
		case Mod:	// TLB errors
		case TLBL:
		case TLBS:
			throw std::runtime_error("TLB exception");

		case AdEL:	// Address error
		case AdES:
		case VCEI:	// Virtual coherency exception
		case VCED:
		case IBE:	// Bus error
		case DBE:
		case Ov:	// Integer overflow
		case Tr:	// Trap
		case SYS:	// System Call
		case Bp:	// Breakpoint
		case RI:	// Reserved Instruction
		case CpU:	// Coprocessor unusable
		case FPE:	// Floating point exception
		case WATCH:	// Watch exception
		case Int:	// Interrupt exception
			generalException();
			break;

		case CacheCode:
			std::cout << "Handling a cache error" << std::endl;
			cacheError();
			break;

		case NMICode:
			NMI();
			break;
		}
	}
	
	return 1;
}


// TODO: method parameters
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

	//TODO: check if kernel mode after reset
	//statusReg.KSU = 0; // set kernel mode
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
// TODO: set cause register
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
		//TODO: set cause register
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

void COP0::raiseException(const COP0::ExceptionCode code)
{
	//clear jump and pending delay as the pc will be reset on the jump inst.
	jumpTarget = 0;
	delaySlot = 0;

	// set the error code
	causeReg.ExcCode = code;

	// unwind the stack and handle the exception in te step method.
	throw code;
}

/*
 * Checks whether the requested coprocessor is usable. If the requested
 * coprocessor can not be used, an appropriate exception is raised.
 */
void COP0::verifyCoprocessorUsability(unsigned int COPnum){
	bool usable = true;

	//if in kernel mode and system coprocessor
	if(statusReg.KSU == 0 && COPnum == 0){
		//Regardless of the CU0 bit setting, CP0 is always usable in
		// Kernel mode.
		return;
	}

	//checking the status register wether the coprocessor is usable
	switch(COPnum){
		case 0: usable = statusReg.CU0; break;
		case 1: usable = statusReg.CU1; break;
		case 2: usable = statusReg.CU2; break;
		case 3: usable = statusReg.CU3; break;
		default:
			// allegrex can have up to 4 coprocessors numbered 0 to 3
			std::runtime_error("COP0: Bad coprocessor number given");
	}

	/* alternate method to check usability
	// bounds checking on input
	if(COPnum > 3){
		throw std::runtime_error("COP0: Bad coprocessor number given");
	}
	//get the apropriate usability bit according to the coprocessor number
	usable = (reg[Status] >> (28 + COPnum) ) & 0x01;
	*/


	//if the requested coprocessor is not usable
	if(!usable){
		//set the coprocessor number in the cause register to be available
		// for the excexption handler
		causeReg.CE = COPnum;
		// and raise the exception
		raiseException(CpU);
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

//	if vAddr_(1..0) ≠ 00b then SignalException(AddressError)
	if(vAddr & 0x00000003){
		return false;
	}
	
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
				throw("COP0: Bad segment");
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
uint32 COP0::loadMemory32(const uint32 vAddr, LoadType role){
//	uint32 pAddr = AddressTranslation(vAddr, DATA);
//	pAddr &= 0xfffffffC;
//	uint32 mem = loadMemory(uncached, WORD, pAddr, vAddr, DATA);
//	cpu.GPR[u.i.rt] = mem;

	if(!validateAddress(vAddr))
		raiseException(AdEL);
	
	bool cachable;
	const uint32 pAddr = addressTranslation(vAddr, cachable);

	//Remove it after cache implementation
//	if(role == INST)
//		cachable = false;

	if(cachable){
		//read from cache
		/*
		const uint32 line = (vAddr & 0x00007fe0) >> 5;
		const uint32 word = vAddr & 0x0000001f;
		dCacheLine &dcl = dCache[line];
		*/
		// TODO: finish cache inomementation
		if(role == DATA)
			return cache.dRead(vAddr, pAddr);
		else // if(role == INST)
			return cache.iRead(vAddr, pAddr);
	}
	else{
		//TODO: abstract bus reading/locking/pending
		//read from memory
		const BusDevice::Request r = {BusDevice::devCPU, BusDevice::devMainMemory, BusDevice::Read, pAddr, 0};

		//enable the flag so to accept the data form the bus
		dataPending = true;

		sendRequest(r);
		//With the current implementation the control will return here after
		// the data are read so no wait is actually needed (but leave it
		// because no harm is done now and for debugging).

		while(dataPending){
			//wait
		}

		return receivedData;
	}
}


void COP0::writeMemory(const uint32 vAddr, const uint32 data)
{
	if(!validateAddress(vAddr))
		raiseException(AdES);

	bool cachable = false;
	const uint32 pAddr = addressTranslation(vAddr, cachable);
	
	//remove it after cache implementation
	cachable = false;

	if(cachable){
		// write to cache
		throw std::runtime_error("COP0: Cache not implemented yet");
	}
	else{
		//create a request to write the data at the appropriate address
		const BusDevice::Request r = {
			BusDevice::devCPU,
			BusDevice::devMainMemory,
			BusDevice::Write,
			pAddr,
			data
		};

		// and reques the write
		sendRequest(r);
	}
}


void COP0::jump(const uint32 target, const bool likely){
	jumpTarget = target;
	if(!likely)
		delaySlot = cpu.PC + (1<<2);
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


void COP0::serviceRequest(const struct BusDevice::Request &req)
{
	if(req.to == BusDevice::devCPUCACHE){
		cache.serviceRequest(req);
		return;
	}

	switch(req.function){
		case BusDevice::Reset:
			reset();
			break;

		case BusDevice::Reply:
			receiveData(req.param1);
			break;
			//systemCoprocessor.

		case BusDevice::Read:
		case BusDevice::Write:
		default:
			throw std::logic_error("COP0: function not recognised");
	}
}

