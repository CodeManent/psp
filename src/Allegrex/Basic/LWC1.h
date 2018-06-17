#ifndef LWC1_H_
#define LWC1_H_
#pragma once

#include "../Instruction.h"


/********************************************************************* p. A-152
 * lwc1 rt, offset(base)
 *
 * The 16-bit offset is sign extended and added to the contents of general
 * register base to form a virtual address. The processor reads a word from
 * the addressed memory location, and makes the data available to coprocessor
 * unit 1.
 *
 * The manner in which the coprocessor used the data is defined by the
 * individual coprocessor specifications.
 * 
 * If either of the two least-significant bits of the effective address are
 * non-zero, an address error exception occurs.
 */

class LWC1 :
	public Instruction
{
public:
	LWC1(const uint32 inst);
	virtual ~LWC1(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
