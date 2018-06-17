#ifndef NOP_H_
#define NOP_H_
#pragma once

#include "../Instruction.h"

class NOP :
	public Instruction
{
public:
	NOP(void);
	virtual ~NOP(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
