#ifndef SB_H_
#define SB_H_
#pragma once

#include "../Instruction.h"

/********************************************************************* p. A-152
 * sb rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of the general
 * register base to form a virtual address. The least significant byte of
 * register rt is stored at the effective address.
 *
 */
class SB :
	public Instruction
{
public:
	SB(const uint32 inst);
	virtual ~SB(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
