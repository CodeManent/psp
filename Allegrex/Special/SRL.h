#ifndef SRL_H_
#define SRL_H_
#pragma once

#include "../Instruction.h"

/*
 * The contents of the general register rt are shifted right by sa bits,
 * inserting zeros into the high-order bits.
 *
 * The result is palced in register rd.
 */
class SRL :
	public Instruction
{
public:
	SRL(const uint32 inst)
	: Instruction(inst){
	}

	virtual ~SRL(void){
	}


	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "srl\t" << strRd() << ", " << strRt() << ", " << strSa();

		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// using unsingned values for hte shift as it is not an arithmetic one
		// but a logical one.
		cpu.GPR[u.r.rd] = cpu.GPR[u.r.rt] >> u.r.sa;
	}
};

#endif
