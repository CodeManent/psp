#ifndef ALLEGREX_MIN_H_
#define ALLEGREX_MIN_H_
#pragma once
#include "../Instruction.h"

class MIN :
	public Instruction
{
public:
	MIN(const uint32 inst);
	virtual ~MIN(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
