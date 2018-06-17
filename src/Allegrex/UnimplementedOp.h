#ifndef UNIMPLEMENTED_OP_H_
#define UNIMPLEMENTED_OP_H_
#pragma once

#include "Instruction.h"

class UnimplementedOp :
	public Instruction
{
public:
	UnimplementedOp();
	UnimplementedOp(const uint32 inst);
	virtual ~UnimplementedOp(void);

	virtual std::string disassemble() const;
	virtual void execute(Allegrex &cpu) const;
	std::string dump(const Allegrex &cpu) const;
};

#endif
