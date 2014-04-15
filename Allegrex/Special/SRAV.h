#ifndef SRAV_H_
#define SRAV_H_
#pragma once

#include "../Instruction.h"

/********************************************************************* p. A-147
 * Shift Right Arithmetic variable
 *
 * srav rd, rt, rs
 *
 * The contents of general register rt are shifted right by the number of bits
 * specified by the low-order five bits of general register rs, sign-extending
 * the high-order bits.
 *
 * The result is placed in register rd.
 *
 */
class SRAV :
	public Instruction
{
public:
	SRAV(const uint32 inst)
	:Instruction(inst){
	}
	virtual ~SRAV(void) = default;

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "srav\t" << strRd() << ", " << strRt() << ", " << strRs();

		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// TODO: check implementation.
		cpu.SGPR[u.r.rd] = cpu.SGPR[u.r.rt] >> (cpu.GPR[u.r.rs] & 0x1f);
	}
};

#endif
