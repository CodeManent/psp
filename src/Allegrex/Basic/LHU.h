#ifndef LHU_H_
#define LHU_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lhu rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The contents os the halfword at
 * the memory location specified by the effective address are zero-extended
 * and loaded into general register rt.
 *
 * If the least-significant bit of the effective address is non-zero,
 * an address error exception occurs.
 */

class LHU :
	public Instruction
{
public:
	LHU(const uint32 inst);
	virtual ~LHU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
