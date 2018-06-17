#ifndef ADDI_H_
#define ADDI_H_
#pragma once

#include "../Instruction.h"

/************************************************************************ p.A-12
 * ADDI rt, rs, immediate
 *
 * The 16-bit immediate is sign-extended and added to the contents of general
 * register rs to form the result. The result is placed into general register rt.
 *
 * An overflow exception occurs if the carries out of bits 30 nd 31 differ
 * (2s complement overflow). The destinatino register rd is not modified when
 * an integer overflow exception occurs.
 */
class ADDI :
	public Instruction
{
public:
	ADDI(const uint32 inst);
	virtual ~ADDI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
