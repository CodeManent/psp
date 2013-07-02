#ifndef BEQ_H_
#define BEQ_H_
#pragma once

#include "../Instruction.h"

class BEQ :
	public Instruction
{
public:
	BEQ(const uint32 inst);
	virtual ~BEQ(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
