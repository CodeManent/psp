#ifndef MSUB_H
#define MSUB_H
#pragma once

#include "../Instruction.h"

/*********************************************************************** p.A-118
 * MSUB rs, rt
 *
 * acc -= rs * rt
 */
class MSUB :
	public Instruction
{
public:
	MSUB(const uint32 inst):Instruction(inst){}
	virtual ~MSUB(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "sub\t" << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		union{
			int64 val;
			struct{
				uint32 lo;
				uint32 hi;
			} U;
		} unpacker;

		unpacker.U.hi = cpu.HI;
		unpacker.U.lo = cpu.LO;
		
		const int64 result =
			static_cast<int64>(cpu.SGPR[u.r.rs])
			*
			static_cast<int64>(cpu.SGPR[u.r.rt]);
		unpacker.val -= result;
		cpu.LO = unpacker.U.lo;
		cpu.HI = unpacker.U.hi;
	}
};

#endif

