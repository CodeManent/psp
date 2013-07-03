#ifndef ALLEGREX_H_
#define ALLEGREX_H_
#pragma once

#include <string>
#include <memory>

#include "../BusDevice.h"

#include "Instruction.h"
#include "COP0.h"

class Allegrex:
	public BusDevice
{
	friend class COP0;

public:
	uint32 GPR[32];		// 32 32bit General Purpose Integer Registers (R0-R31)
	int32 *SGPR;

	uint32 PC;			// program counter
//	uint32 nextPC;		// delay slot
	uint32 HI;			// Integer multiply/divide result HI
	uint32 LO;			// Integer multiply/divide result LO

	uint32 debug_registers[32];

	uint32 CPR[3][32];	//coprocessor registers;
	uint32 CCR[3][32];	//coprocessor control registers
	uint32 COC[3];

	COP0 systemCoprocessor;

	Allegrex(PSP *bus);
	~Allegrex(void);

	static std::unique_ptr<Instruction> decode(const uint32 &inst);

	void execute(const uint32 &inst);

	virtual void serviceRequest(const struct Request &req);
	//void cppIsTroll(const struct Request &req);

//	uint32& getGPR(const uint32 r);
//	uint32& getCPR(const uint32 cop, const uint32 r);
//	uint32& getCCR(const uint32 cop, const uint32 r);
//	uint32& getCOC(const uint32 cop);

//	INSTRUCTION unpack(const uint32 inst) const;

	enum Register{
		zero = 0,		//wired zero
		at,				//assembler temp

		v0, v1,			//return value

		a0, a1, a2, a3,	//argument registers
		
		t0, t1, t2, t3,	//caller saved (o32 old style names: default)
		t4, t5, t6, t7,

		s0, s1, s2, s3, //calee saved
		s4, s5, s6, s7,

		t8, t9,			//caller saved

		k0, k1,			//kernel temporary

		gp,				//global pointer
		sp,				// stack pointer
		fp,				// frame pointer
		s8 = fp,		// other name for frame pointer
		ra				//return address
	};

	enum Opcodes{
		opSPECIAL = 0x00,
		opREGIMM = 0x01,
		opJ		= 0x2,
		opJAL	= 0x3,
		opBEQ	= 0x4,
		opBNE	= 0x5,
		opBLEZ	= 0x6,
		opBGTZ	= 0x7,
		opADDI	= 0x8,
		opADDIU	= 0x9,
		opSLTI	= 0xA,
		opSLTIU	= 0xB,
		opANDI	= 0xC,
		opORI	= 0xD,
		opXORI	= 0xE,
		opLUI	= 0xF,
		opCOP0	= 0x10,
		opCOP1	= 0x11,
		opVFPU2	= 0x12,
		//0x13 reserved or unsupported
		opBEQL	= 0x14,
		opBNEL	= 0x15,
		opBLEZL	= 0x16,
		opBGTZL	= 0x17,
		opVFPU0	= 0x18,
		opVFPU1	= 0x19,
		/*  0x1a reserved or unsupported */
		opVFPU3	= 0x1b,
		opSPECIAL2	= 0x1c,
		/*  0x1d reserved or unsupported */
		/*  0x1e reserved or unsupported */
		opSPECIAL3	= 0x1f,
		opLB	= 0x20,
		opLH	= 0x21,
		opLWL	= 0x22,
		opLW	= 0x23,
		opLBU	= 0x24,
		opLHU	= 0x25,
		opLWR	= 0x26,
		/*  0x27 reserved or unsupported */
		opSB	= 0x28,
		opSH	= 0x29,
		opSWL	= 0x2A,
		opSW	= 0x2B,
		/*  0x2c reserved or unsupported */
		/*  0x2d reserved or unsupported */
		opSWR	= 0x2E,
		opCACHE	= 0x2f,
		opLL	= 0x30,
		opLWC1	= 0x31,
		opLVS	= 0x32,
		/*  0x32 reserved or unsupported */
		/*  0x33 reserved or unsupported */
		opVFPU4	= 0x34,
		opULVQ	= 0x35,
		opLVQ	= 0x36,
		opVFPU5	= 0x37,
		opSC	= 0x38,
		opSWC1	= 0x39,
		opSVS	= 0x3a,
		/*  0x3b reserved or unsupported */
		opVFPU6	= 0x3c,
		opUSVQ	= 0x3d,
		opSVQ	= 0x3e,
		opVFPU7	= 0x3f// SPECIAL: encoded by function field when opcode field = SPECIAL
	};
	enum SpecialOpcodes{
		opNOP	= 0x00,
		opSLL	= 0x0,
		/*  0x1 reserved or unsupported */
		opSRLROR = 0x2,
		opSRA	= 0x3,
		opSLLV	= 0x4,
		/*  0x5 reserved or unsupported */
		opSRLRORV = 0x6,
		opSRAV	= 0x7,
		opJR	= 0x8,
		opJALR	= 0x9,
		opMOVZ	= 0xa,
		opMOVN	= 0xb,
		opSYSCALL = 0xc,
		opBREAK	= 0xd,
		/*  0xe reserved or unsupported */
		opSYNC	= 0xf,
		opMFHI	= 0x10,
		opMTHI	= 0x11,
		opMFLO	= 0x12,
		opMTLO	= 0x13,
		/*  0x14 reserved or unsupported */
		/*  0x15 reserved or unsupported */
		opCLZ	= 0x16,
		opCLO	= 0x17,
		opMULT	= 0x18,
		opMULTU	= 0x19,
		opDIV	= 0x1a,
		opDIVU	= 0x1b,
		opMADD	= 0x1c,
		opMADDU	= 0x1d,
		/*  0x1e reserved or unsupported */
		/*  0x1f reserved or unsupported */
		opADD	= 0x20,
		opADDU	= 0x21,
		opSUB	= 0x22,
		opSUBU	= 0x23,
		opAND	= 0x24,
		opOR	= 0x25,
		opXOR	= 0x26,
		opNOR	= 0x27,
		/*  0x28 reserved or unsupported */
		/*  0x29 reserved or unsupported */
		opSLT	= 0x2a,
		opSLTU	= 0x2b,
		opMAX		= 0x2c,
		opMIN	= 0x2d,
		opMSUB	= 0x2e,
		opMSUBU	= 0x2f
	};
};

#endif
