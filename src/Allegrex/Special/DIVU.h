#ifndef DIVU_H_
#define DIVU_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p.A-59
 * DIVU rs, rt
 *
 * The contents of general register rs are divided by the contents of general
 * register rt, treating both values as unsigned values. No integer overflow
 * exception occurs under any circumstances, and the result of this operation
 * is undefined when the divisor is zero.
 *
 * This instruction is typically followed by aditional instructions to check for
 * a zero divisor.
 *
 * When the operation completes, the quotient word ot the double result is
 * loaded into special register LO and the remainder word of the double result
 * is loaded into special register HI.
 *
 * If either of two preceding instructions is MFHI of MFLO, the results of these
 * instructions are undefined. Correct operation requires separating reads of
 * HI or LO from writes by a minimum of two other instructions.
 */
class DIVU :
	public Instruction
{
public:
	DIVU(const uint32 inst):Instruction(inst){}
	virtual ~DIVU(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "divu\t" << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.LO = cpu.GPR[u.r.rs] / cpu.GPR[u.r.rt];
		cpu.HI = cpu.GPR[u.r.rs] % cpu.GPR[u.r.rt];
	}
};

#endif
