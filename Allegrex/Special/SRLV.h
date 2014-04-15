#ifndef SRLV_H_
#define SRLV_H_
#pragma once

#include "../Instruction.h"

/********************************************************************* p. A-149
 * Shift Right Logical Variable
 *
 * The contents of general register rt are shifted right by the number of bits
 * specified by the low-order five bits of general register rs, inserting zeros
 * into the high order bits.
 *
 * The result is placed in register rd.
 */
class SRLV :
	public Instruction
{
public:
	SRLV(const uint32 inst)
	: Instruction(inst){
	}

	virtual ~SRLV(void){
	}


	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "srlv\t" << strRd() << ", " << strRt() << ", " << strRs();

		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// using unsingned values for hte shift as it is not an arithmetic one
		// but a logical one.
		cpu.GPR[u.r.rd] = cpu.GPR[u.r.rt] >> (cpu.GPR[u.r.rs] & 0x0000001F);
	}
};

#endif
