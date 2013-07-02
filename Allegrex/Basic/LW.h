#ifndef LW_H_
#define LW_H_
#pragma once

#include "../Instruction.h"

class LW :
	public Instruction
{
public:
	LW(const uint32 inst);
	virtual ~LW(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
