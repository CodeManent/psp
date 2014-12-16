#ifndef SWL_H_
#define SWL_H_
#pragma once

#include "../Instruction.h"


/*****************************************************************************
 * swl rt, offset(base)
 *
 * Stores the most dignificant part of a word to an unaligned memory address.
 *
 * The 16-bit sign offset is added to the contents of GPR base to form an
 * effective address (EffAddr). EffAddr is the address of the most significant
 * of 4 consecutive bytes forming a word (W) in memory startig at an arbitary
 * byte boundary.
 *
 * A part of W, the most significant 1 to 4 bytes, is in the aligned word
 * containing EffAddr. The same number of the most-significant (left) bytes
 * from the word in GPR rt are stored into these bytes of W.
 *
 * No address exceptions due to alignment are possible.
 */

class SWL :
	public Instruction
{
public:
	SWL(const uint32 inst);
	virtual ~SWL(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
