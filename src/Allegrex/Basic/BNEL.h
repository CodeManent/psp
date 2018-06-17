#ifndef BNEL_H_
#define BNEL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-40
 *BNEL rs, rt, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. The contents of general register rt and the contents of
 * general register rt are compared. If the two registers are not equal, then
 * the program branches to the target address, with a delay of one instruction.
 *
 * If the conditional branch is not taken, the instruction in the delay slot is nullified.
 */
class BNEL :
	public Instruction
{
public:
	BNEL(const uint32 inst):Instruction(inst){}
	virtual ~BNEL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bnel\t" << strRs() << ", " << strRt() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		bool condition = (cpu.GPR[u.i.rs] != cpu.GPR[u.i.rt]);
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4, true);
		}
	}
};

#endif
