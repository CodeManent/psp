#ifndef MULT_H_
#define MULT_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p.A-118
 * MULT rs, rt
 *
 * The contents of general registers rs and rt are multiplied, treating both
 * values as 32bit 2's comomplement values. No integer overflow exception occurs
 * under any circumstances.
 *
 * When the operation completes, the low-order word of the double result is
 * loaded into special register LO and the high-order word of the double result
 * is loaded into special register HI.
 *
 * If either of two preceding instructions is MFHI of MFLO, the results of these
 * instructions are undefined. Correct operation requires separating reads of
 * HI or LO from writes by a minimum of two other instructions.
 */
class MULT :
	public Instruction
{
public:
	MULT(const uint32 inst):Instruction(inst){}
	virtual ~MULT(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "mult\t" << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		const uint64 result = static_cast<int64>(cpu.SGPR[u.r.rs])
		                    * static_cast<int64>(cpu.SGPR[u.r.rt]);
		cpu.LO = static_cast<uint32>(result);
		cpu.HI = static_cast<uint32>(result >> 32);
	}
};

#endif
