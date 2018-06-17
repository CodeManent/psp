#ifndef MSUBU_H_
#define MSUBU_H_
#pragma once

#include "../Instruction.h"

/*********************************************************************** p.A-118
 * MSUBU rs, rt
 *
 * acc -= rs * rt
 */
class MSUBU :
	public Instruction
{
public:
	MSUBU(const uint32 inst):Instruction(inst){}
	virtual ~MSUBU(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "sub\t" << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		union{
			uint64 val;
			struct{
				uint32 lo;
				uint32 hi;
			} U;
		} unpacker;

		unpacker.U.hi = cpu.HI;
		unpacker.U.lo = cpu.LO;
		
		const int64 result =
			static_cast<uint64>(cpu.GPR[u.r.rs])
			*
			static_cast<uint64>(cpu.GPR[u.r.rt]);
		unpacker.val -= result;
		cpu.LO = unpacker.U.lo;
		cpu.HI = unpacker.U.hi;
	}
};

#endif

