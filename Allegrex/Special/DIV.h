#ifndef DIV_H_
#define DIV_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p.A-57
 * DIV rs, rt
 *
 * The contents of general registers rs are divided by the contents of general
 * register rt, treating both values as 32bit 2's complement values. No integer
 * overflow exception occurs under any circumstances, and the result of this
 * operation is undefined when the divisor is zero.
 *
 * This instruction is typically followed by aditional instructions to check for
 * a zero divisor and for overflow.
 *
 * When the operation completes, the quotient word ot the double result is
 * loaded into special register LO and the remainder word of the double result
 * is loaded into special register HI.
 *
 * If either of two preceding instructions is MFHI of MFLO, the results of these
 * instructions are undefined. Correct operation requires separating reads of
 * HI or LO from writes by a minimum of two other instructions.
 */
class DIV :
	public Instruction
{
public:
	DIV(const uint32 inst):Instruction(inst){}
	virtual ~DIV(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "div\t" << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.LO = cpu.SGPR[u.r.rs] / cpu.SGPR[u.r.rt];
		cpu.HI = cpu.SGPR[u.r.rs] % cpu.SGPR[u.r.rt];
	}
};

#endif
