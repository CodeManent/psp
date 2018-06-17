#ifndef MOVZ_H_
#define MOVZ_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-113
 * MOVZ rd, rs, rt
 *
 */
class MOVZ :
	public Instruction
{
public:
	MOVZ(const uint32 inst):Instruction(inst){}
	virtual ~MOVZ(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "movz\t" << strRd() << ", " << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		if(cpu.GPR[u.r.rt] == 0)
			cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs];
	}
};

#endif
