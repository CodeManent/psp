#ifndef JAL_H_
#define JAL_H_
#pragma once

#include "../Instruction.h"

class JAL :
	public Instruction
{
public:
	JAL(const uint32 inst);
	virtual ~JAL(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
