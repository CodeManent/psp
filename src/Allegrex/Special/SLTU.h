#ifndef SLTU_H_
#define SLTU_H_
#pragma once
#include "../Instruction.h"

class SLTU :
	public Instruction
{
public:
	SLTU(const uint32 inst);
	virtual ~SLTU(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
