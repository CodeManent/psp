#ifndef J_H_
#define J_H_
#pragma once

#include "../Instruction.h"

class J :
	public Instruction
{
public:
	J(const uint32 inst);
	virtual ~J(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
