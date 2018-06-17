#ifndef NOR_H_
#define NOR_H_
#pragma once
#include "../Instruction.h"

class NOR :
	public Instruction
{
public:
	NOR(const uint32 inst);
	virtual ~NOR(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
