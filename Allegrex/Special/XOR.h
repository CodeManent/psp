#ifndef XOR_H_
#define XOR_H_
#pragma once
#include "../Instruction.h"

class XOR :
	public Instruction
{
public:
	XOR(const uint32 inst);
	virtual ~XOR(void);

	std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
