#ifndef SLTI_H_
#define SLTI_H_
#pragma once

#include "../Instruction.h"

class SLTI :
	public Instruction
{
public:
	SLTI(const uint32 inst);
	virtual ~SLTI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
