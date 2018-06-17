#ifndef SRA_H_
#define SRA_H_
#pragma once

#include "../Instruction.h"

class SRA :
	public Instruction
{
public:
	SRA(const uint32 inst);
	virtual ~SRA(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
