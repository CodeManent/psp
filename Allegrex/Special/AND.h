#ifndef AND_H_
#define AND_H_
#pragma once
#include "../Instruction.h"

class AND :
	public Instruction
{
public:
	AND(const uint32 inst);
	virtual ~AND(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
