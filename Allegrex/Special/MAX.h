#ifndef ALLEGREX_MAX_H_
#define ALLEGREX_MAX_H_
#pragma once
#include "../Instruction.h"

class MAX :
	public Instruction
{
public:
	MAX(const uint32 inst);
	virtual ~MAX(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
