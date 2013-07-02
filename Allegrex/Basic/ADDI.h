#ifndef ADDI_H_
#define ADDI_H_
#pragma once

#include "../Instruction.h"

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
