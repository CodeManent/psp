#ifndef MOVN_H_
#define MOVN_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-113
 * MOVN rd, rs, rt
 *
 */
class MOVN :
	public Instruction
{
public:
	MOVN(const uint32 inst):Instruction(inst){}
	virtual ~MOVN(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "movn\t" << strRd() << ", " << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		if(cpu.GPR[u.r.rt] != 0)
			cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs];
	}
};

#endif
