#ifndef ROTR_H_
#define ROTR_H_
#pragma once

#include "../Instruction.h"

/*
 * TODO: check ROTR instruction and fill in sme description.
 * I assube it must be rotate right with the shift amount showing how many
 * bits to rorate.
 */
class ROTR :
	public Instruction
{
public:
	ROTR(const uint32 inst)
	: Instruction(inst){
	}

	virtual ~ROTR(void){
	}


	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "rotr\t" << strRd() << ", " << strRt() << ", " << strSa();

		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		cpu.GPR[u.r.rd] = (cpu.GPR[u.r.rt] >> u.r.sa) | (cpu.GPR[u.r.rt] << (32 - u.r.sa));
	}
};

#endif
