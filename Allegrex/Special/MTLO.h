#ifndef MTLO_H_
#define MTLO_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-116
 * MTLO rd
 *
 * The contents of the general register rs are loaded into special register LO.
 *
 * If a MTLO operation is executed following a MULT, MULTU, DIV or DIVU
 * instruction, but before any MFLO, MFHT, MTLO or MTLO instructions, the
 * contents of special register HI are unsefined.
 */
class MTLO :
	public Instruction
{
public:
	MTLO(const uint32 inst):Instruction(inst){}
	virtual ~MTLO(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "mtlo\t" << strRs();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.LO = cpu.GPR[u.r.rs];
	}
};

#endif
