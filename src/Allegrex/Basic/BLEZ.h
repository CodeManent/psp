#ifndef BLEZ_H_
#define BLEZ_H_
#pragma once

#include "../Instruction.h"

class BLEZ :
	public Instruction
{
public:
	BLEZ(const uint32 inst);
	virtual ~BLEZ(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
