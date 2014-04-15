#ifndef ALLEGREX_COP0_ERET_H_
#define ALLEGREX_COP0_ERET_H_

#include "../Instruction.h"

/********************************************************************** p. A-76
 * Exception Retun
 *
 * eret
 *
 * ERET is the R4000 instruction for returning from an interrupt, exception,
 * or error trap. Unlike a branch or jump instruction, ERET does not execute
 * the next instruction .
 *
 * ERET must not itself be palced in a branch delay slot.
 *
 * If the processor is servicing an error trap (SR_2 = 1), then load the PC
 * from the ErrorEPC and clear the ERL bit of tghe status register (SR_2).
 * Otherwise (SR_2 = 0), load the PC from the EPC, anc clear the EXL bit of
 * the status register (SR_1).
 *
 * An ERET executed between an LL and SCalso causes the SC to fail.
 *
 */
class ERET: public Instruction{
public:
	ERET(uint32 inst);
	virtual ~ERET() = default;

	virtual std::string disassemble() const;

	virtual void execute(Allegrex &cpu) const;
};

#endif

