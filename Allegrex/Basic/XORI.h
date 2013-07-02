#ifndef XORI_H_
#define XORI_H_
#pragma once

#include "../Instruction.h"

class XORI :
	public Instruction
{
public:
	XORI(const uint32 inst);
	virtual ~XORI(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
