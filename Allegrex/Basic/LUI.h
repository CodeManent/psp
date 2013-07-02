#ifndef LUI_H_
#define LUI_H_
#pragma once

#include "../Instruction.h"

class LUI :
	public Instruction
{
public:
	LUI(const uint32 inst);
	virtual ~LUI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
