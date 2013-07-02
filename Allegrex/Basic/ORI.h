#ifndef ORI_H_
#define ORI_H_
#pragma once

#include "../Instruction.h"

class ORI :
	public Instruction
{
public:
	ORI(const uint32 inst);
	virtual ~ORI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
