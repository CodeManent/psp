#ifndef OR_H_
#define OR_H_
#pragma once
#include "../Instruction.h"

class OR :
	public Instruction
{
public:
	OR(const uint32 inst);
	virtual ~OR(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
