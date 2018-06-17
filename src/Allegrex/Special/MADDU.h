#ifndef MADDU_H_
#define MADDU_H_
#pragma once

#include "../Instruction.h"

/*********************************************************************** p.A-118
 * MADDU rs, rt
 *
 * acc += rs * rt
 */
class MADDU :
	public Instruction
{
public:
	MADDU(const uint32 inst):Instruction(inst){}
	virtual ~MADDU(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "maddu\t" << strRs() << ", " << strRt();

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
		
		const uint64 result =
			static_cast<uint64>(cpu.GPR[u.r.rs])
			*
			static_cast<uint64>(cpu.GPR[u.r.rt]);
		unpacker.val += result;
		cpu.LO = unpacker.U.lo;
		cpu.HI = unpacker.U.hi;
	}
};

#endif

