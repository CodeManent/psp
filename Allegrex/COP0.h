#ifndef COP0_H_
#define COP0_H_
#pragma once

#include "Coprocessor.h"
#include "../BusDevice.h"
#include "Cache.h"

class COP0: public Coprocessor, public BusDevice
{
	friend class ERET;
	friend class  CACHE;
	// *****THERE IS NO TLB IN ALLEGREX*****

	// two helping vars to handle the branching instructions
	uint32 jumpTarget;
	uint32 delaySlot;
	bool LLbit;
	Cache cache;

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
};

#endif
