#ifndef SLT_H_
#define SLT_H_
#pragma once
#include "../Instruction.h"

class SLT :
	public Instruction
{
public:
	SLT(const uint32 inst);
	virtual ~SLT(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
