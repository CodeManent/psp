#ifndef LBU_H_
#define LBU_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lbu rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The contents of  the byte at the
 * memory location specified by the effective address.are sign extended and
 * loaded into general register rt.
 */

class LBU :
	public Instruction
{
public:
	LBU(const uint32 inst);
	virtual ~LBU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
