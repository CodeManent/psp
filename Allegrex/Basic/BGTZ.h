#ifndef BGTZ_H_
#define BGTZ_H_
#pragma once

#include "../Instruction.h"

class BGTZ :
	public Instruction
{
public:
	BGTZ(const uint32 inst);
	virtual ~BGTZ(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
