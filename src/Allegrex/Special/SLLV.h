#ifndef SLLV_H_
#define SLLV_H_
#pragma once

#include "../Instruction.h"

class SLLV :
	public Instruction
{
public:
	SLLV(const uint32 inst);
	virtual ~SLLV(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
};

#endif
