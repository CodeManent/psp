#ifndef ADDU_H_
#define ADDU_H_
#pragma once

#include "../Instruction.h"

class ADDU :
	public Instruction
{
public:
	ADDU(const uint32 inst);
	virtual ~ADDU(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
