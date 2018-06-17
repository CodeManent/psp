#ifndef SUBU_H_
#define SUBU_H_
#pragma once
#include "../Instruction.h"

class SUBU :
	public Instruction
{
public:
	SUBU(const uint32 inst);
	virtual ~SUBU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
