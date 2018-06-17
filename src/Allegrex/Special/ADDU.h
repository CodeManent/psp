#ifndef ADDU_H_
#define ADDU_H_
#pragma once

#include "../Instruction.h"

/************************************************************************ p.A-14
 * ADDU rd, rs, rt
 *
 * The contents of the general register sr and the contents of the general
 * register rt are added to form the result. The result is placed into general
 * register rd. No overflow exception occurs under any circumstances.
 *
 * The only difference between this instruction and the ADD instruction is that
 * ADDU never causes an overflow exception.
 */
 
class ADDU :
	public Instruction
{
public:
	ADDU(const uint32 inst);
	virtual ~ADDU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
