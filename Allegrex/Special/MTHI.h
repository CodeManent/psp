#ifndef MTHI_H_
#define MTHI_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-116
 * MTHI rd
 *
 * The contents of the general register rs are loaded into special register HI.
 *
 * If the MTHI operation is executed following a MULT, MULTU, DIV or DIVU
 * instruction, but before any MFLO, MFHT, MTLO or MTHI instructions, the
 * fcontents of special register LO are unsefined.
 */
class MTHI :
	public Instruction
{
public:
	MTHI(const uint32 inst):Instruction(inst){}
	virtual ~MTHI(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "mthi\t" << strRs();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.HI = cpu.GPR[u.r.rs];
	}
};

#endif
