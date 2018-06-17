#ifndef BGEZALL_H_
#define BGEZALL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-29
 * Branch On Greater Than Or Equal To Zero And Link Likely
 *
 * BGEZALL rs, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. Uncoditionally, the address of the instruction after the delay
 * slot is placed in the link register r31. If the contents of general register
 * rs have the sign bit cleared, then the program branches to the target
 * address, with a delay of one instruction.
 *
 * If the conditional branch is not taken, the instruction in the delay slot is
 * nullified
 */
class BGEZALL :
	public Instruction
{
public:
	BGEZALL(const uint32 inst):Instruction(inst){}
	virtual ~BGEZALL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bgezall\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		cpu.GPR[31] = cpu.PC + 8;
		// get the sign bit
		bool condition = (cpu.GPR[u.i.rs] & 0x80000000) == 0;
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4, true);
		}
	}
};

#endif

