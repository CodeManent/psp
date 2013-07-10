#ifndef ANDI_H_
#define ANDI_H_
#pragma once

#include "../Instruction.h"

/************************************************************************ p.A-16
 * ANDI rd, rs, rt
 *
 * The 16-bit immediate is zero-extended and combined with the contents of
 * general regiater rs in a bit-wise logical AND operation. The result is placed
 * into general register rt.
 */
 
class ANDI :
	public Instruction
{
public:
	ANDI(const uint32 inst);
	virtual ~ANDI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
