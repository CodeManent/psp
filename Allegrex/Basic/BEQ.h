#ifndef BEQ_H_
#define BEQ_H_
#pragma once

#include "../Instruction.h"

/************************************************************************ p.A-25
 * BEQ rs, rt, offset
 *
 * A branch target address is computed from the sum of the adress of the
 * instruction in the delay slot and the 16-bit offset, shifted left two bits
 * and sign extended. the contents of general refiater rs and the contents of
 * general register rt are compared. If the two registers are equal, then the
 * program branches to target adress, with a delay of one instruction.
 *
 * target ← (offset_15)^14 || offset || 00
 * condition ← (GPR[rs] = GPR[rt])
 * if condition then
 *     PC ← PC + target
 * endif
 */
class BEQ :
	public Instruction
{
public:
	BEQ(const uint32 inst);
	virtual ~BEQ(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
