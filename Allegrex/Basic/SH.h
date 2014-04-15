#ifndef SH_H_
#define SH_H_
#pragma once

#include "../Instruction.h"

/********************************************************************* p. A-152
 * sh rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of the general
 * register base to form a virtual address. The least significant halfword of
 * register rt is stored at the effective address.
 *
 * If the least significant bit of the effctive address is non-zero, an address
 * error exception occurs.
 */
class SH :
	public Instruction
{
public:
	SH(const uint32 inst);
	virtual ~SH(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
