#ifndef ANDI_H_
#define ANDI_H_
#pragma once

#include "../Instruction.h"

class ANDI :
	public Instruction
{
public:
	ANDI(const uint32 inst);
	virtual ~ANDI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
