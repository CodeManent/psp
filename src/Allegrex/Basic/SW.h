#ifndef SW_H_
#define SW_H_
#pragma once

#include "../Instruction.h"

class SW :
	public Instruction
{
public:
	SW(const uint32 inst);
	virtual ~SW(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
