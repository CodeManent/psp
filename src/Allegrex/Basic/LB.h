#ifndef LB_H_
#define LB_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lb rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The contents of  the byte at the
 * memory location specified by the effective address.are sign extended and
 * loaded into general register rt.
 */

class LB :
	public Instruction
{
public:
	LB(const uint32 inst);
	virtual ~LB(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
