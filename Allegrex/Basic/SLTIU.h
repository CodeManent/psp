#ifndef SLTIU_H_
#define SLTIU_H_
#pragma once

#include "../Instruction.h"

class SLTIU :
	public Instruction
{
public:
	SLTIU(const uint32 inst);
	virtual ~SLTIU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
