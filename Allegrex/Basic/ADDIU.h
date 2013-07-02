#ifndef ADDIU_H_
#define ADDIU_H_
#pragma once

#include "../Instruction.h"

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
