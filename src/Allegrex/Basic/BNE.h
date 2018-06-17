#ifndef BNE_H_
#define BNE_H_
#pragma once

#include "../Instruction.h"

class BNE :
	public Instruction
{
public:
	BNE(const uint32 inst);
	virtual ~BNE(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
