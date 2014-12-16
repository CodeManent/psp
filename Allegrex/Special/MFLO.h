#ifndef MFLO_H_
#define MFLO_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-113
 * MFLO rd
 *
 * The contents of special register LO are loaded into general register rd.
 *
 * To ensure proper operation in the event of interrupts, the two instructions
 * which follow a MFLO instruction may not be any of the instructions which
 * modify the LO register: MULT, MULTU, DIV, DIVU, MHTI, DMULT, DMULTU, DDIV, DDIVU.
 */
class MFLO :
	public Instruction
{
public:
	MFLO(const uint32 inst):Instruction(inst){}
	virtual ~MFLO(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "mflo\t" << strRd();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.GPR[u.r.rd] = cpu.LO;
	}
};

#endif
