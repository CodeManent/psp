#ifndef SLL_H_
#define SLL_H_
#pragma once

#include "../Instruction.h"

class SLL :
	public Instruction
{
public:
	SLL(const uint32 inst);
	virtual ~SLL(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
