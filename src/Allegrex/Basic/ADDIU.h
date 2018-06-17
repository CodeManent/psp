#ifndef ADDIU_H_
#define ADDIU_H_
#pragma once

#include "../Instruction.h"

/************************************************************************ p.A-12
 * ADDIU rt, rs, immediate
 *
 * The 16-bit immediate is sign-extended and added to the contents of general
 * register rs to form the result. The result is placed into general register rt.
 * No integer overflow exception occurs under any circumstances.
 *
 * The only difference between this instruction and the ADDI instruction is that
 * ADDIU never causes an overflow exception.
 */
class ADDIU :
	public Instruction
{
public:
	ADDIU(const uint32);
	virtual ~ADDIU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
