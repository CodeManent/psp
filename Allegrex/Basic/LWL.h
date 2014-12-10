#ifndef LWL_H_
#define LWL_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A102
 * lwl rt, offset(base)
 *
 * The LWL instruction adds its sign-extended 16-bit offset to the contents
 * of general register base to form a virtual sddresswhich can specify an
 * arbitary byte. It reads bytes only from the word in memory which contains
 * the specified starting byte.
 *
 * Conceptually it starts at the specified byte in memory and loads that byte
 * into the high-order (left-most) byte of the register; then it loads bytes
 * from memory into the register until it reaches the low-order byte of the
 * word in memory. The least significant (tight-most) byte(s) of the register
 * will not be chanded.
 *
 * No address exceptions due to alignment are possible.
 */

class LWL :
	public Instruction
{
public:
	LWL(const uint32 inst);
	virtual ~LWL(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
