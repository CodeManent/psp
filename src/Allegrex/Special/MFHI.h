#ifndef MFHI_H_
#define MFHI_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-112
 * MFHI rd
 *
 * The contents of special register HI are loaded into general register rd.
 *
 * To ensure proper operation in the event of interrupts, the two instructions
 * which follow a MFHI instruction may not be any of the instructions which
 * modify the HI register: MULT, MULTU, DIV, DIVU, MHTI, DMULT, DMULTU, DDIV, DDIVU.
 */
class MFHI :
	public Instruction
{
public:
	MFHI(const uint32 inst):Instruction(inst){}
	virtual ~MFHI(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "mfhi\t" << strRd();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.GPR[u.r.rd] = cpu.HI;
	}
};

#endif
