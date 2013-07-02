#ifndef JR_H_
#define JR_H_
#pragma once

#include "../Instruction.h"

class JR :
	public Instruction
{
public:
	JR(const uint32 inst);
	virtual ~JR(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif