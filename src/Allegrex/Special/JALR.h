#ifndef JALR_HPP
#define JALR_HPP
#pragma once

#include "../Instruction.h"

class JALR :
    public Instruction
{
public:
    JALR(const uint32 inst);
    virtual ~JALR(void);

    virtual std::string disassemble() const;
    virtual void execute(Allegrex &cpu) const;
};

#endif // JALR_HPP
