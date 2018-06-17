#ifndef AND_H_
#define AND_H_
#pragma once
#include "../Instruction.h"

/************************************************************************ p.A-15
 * AND rd, rs, rt
 *
 * The contents of the general register rs are combined with the contents of
 * general register rt in a bit-wise logical AND operation. The result is placed
 * into general register rd.
 */
 
class AND :
	public Instruction
{
public:
	AND(const uint32 inst);
	virtual ~AND(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
