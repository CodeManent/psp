#ifndef ROTRV_H_
#define ROTRV_H_
#pragma once

#include "../Instruction.h"

/*
 * Rotate Right Variable
 *
 * TODO: check ROTRV instruction and fill in some description.
 * I assume it must be rotate right with the shift amount showing how many
 * bits to rorate.
 */
class ROTRV :
	public Instruction
{
public:
	ROTRV(const uint32 inst)
	: Instruction(inst){
	}

	virtual ~ROTRV(void){
	}


	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "rotrv\t" << strRd() << ", " << strRt() << ", " << strRs();

		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// hopefully this is a rotate, can't check it now
		// TODO: check rotate impementation
		cpu.GPR[u.r.rd] =
			(cpu.GPR[u.r.rt] >> u.r.sa)
			|
			(cpu.GPR[u.r.rt] << (32 - (cpu.GPR[u.r.rs] & 0x0000001F)));
	}
};

#endif
