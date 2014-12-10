#ifndef LWR_H_
#define LWR_H_
#pragma once

#include "../Instruction.h"


/*****************************************************************************
 * lwr rt, offset(base)
 *
 * Loads the least significant part of a word from an unaligned memory address
 * as a signed value.
 *
 * The 16-bit signed offset is added to the contents of the GPR base to form
 * an effective address (EffAddr). EffAddr is the address of the least
 * significant of 4 consecutive bytes forming a word (W) in memory starting at
 * an arbitary byte boundry.
 *
 * A part of W, the leas significant 1 to 4 bytes, is in the aligned word
 * containing EffAddr. This part of W is loaded into the leas significant
 * (right) part of the word int GPR rt. The remainig most-significant part of
 * the word in GPR rt is unchanged.
 *
 * Executing both LWL abd LWR, in either order, delivers a sign-extended word
 * value in the destination register.
 *
 * No address exceptions due to alignment are possible.
 */

class LWR :
	public Instruction
{
public:
	LWR(const uint32 inst);
	virtual ~LWR(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
