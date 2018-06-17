#ifndef LH_H_
#define LH_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lh rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The contents os the halfword at
 * the memory location specified by the effective address are sign-extended
 * and loaded into general register rt.
 *
 * If the least-significant bit of the effective address is non-zero,
 * an address error exception occurs.
 */

class LH :
	public Instruction
{
public:
	LH(const uint32 inst);
	virtual ~LH(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
