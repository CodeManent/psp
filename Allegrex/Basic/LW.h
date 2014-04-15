#ifndef LW_H_
#define LW_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lw rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The contents of general register rt
 * are stored at the memory location specified by the effective address.
 *
 * If either of the two least-significant bits of the effective address are
 * non-zero, an address error exception occurs.
 */

class LW :
	public Instruction
{
public:
	LW(const uint32 inst);
	virtual ~LW(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
