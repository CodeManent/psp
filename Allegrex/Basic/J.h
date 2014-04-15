#ifndef J_H_
#define J_H_
#pragma once

#include "../Instruction.h"

/********************************************************************** p. A-77
 * j target
 *
 * The 26-bit target address is shifted left two bits and combined with high
 * order bits of the address of the delay slot. The program unconditionally
 * jumps to this calculated address with a delay of one instruction.
 */
class J :
	public Instruction
{
public:
	J(const uint32 inst);
	virtual ~J(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
