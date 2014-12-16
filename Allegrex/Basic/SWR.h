#ifndef SWR_H_
#define SWR_H_
#pragma once

#include "../Instruction.h"


/*****************************************************************************
 * swr rt, offset(base)
 *
 * Stores the least significant part of a word to an unaligned memory address.
 *
 * The 16-bit signed offset is added to the contents of GPR base to form an
 * effective address (EffAddr). EffAddr is the address of the least significant
 * of 4 consecutive bytes forming a word (W) in memory startig at an arbitary
 * byte boundary.
 *
 * A part of W, the least significant 1 to 4 bytes, is in the aligned word
 * containing EffAddr. The same number of the least-significant (iright) bytes
 * from the word in GPR rt are stored into these bytes of W.
 *
 * No address exceptions due to alignment are possible.
 */

class SWR :
	public Instruction
{
public:
	SWR(const uint32 inst);
	virtual ~SWR(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
