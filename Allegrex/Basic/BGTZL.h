#ifndef BGTZL_H_
#define BGTZL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-32
 * BGTZL rs, offset
 *
 * A branch target is computedd from the sum of the address of the instruction
 * in the delay slot and the 16bit offset, shifted left two bits and sign
 * extended. The contents of general register rs are compared to zero. If the
 * contents of general register rs have the sign bit cleared and are not equal to
 * zero, thenthe program branches to the target address, with a delay of one
 * instruction. If the conditional branch is not taken, the instruction in the
 * delay slot is nullified.
 *
 */

class BGTZL :
	public Instruction
{
public:
	BGTZL(const uint32 inst):Instruction(inst){};
	virtual ~BGTZL(void){};

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bgtzl\t" << strRs() << ", " << strOffset();
		return ss.str();
	}
	virtual void execute(Allegrex &cpu) const{
		bool condition = (cpu.SGPR[u.i.rs] > 0);
		if(condition){
			uint32 target = cpu.PC +  expandOffset();
			jump(cpu, target + 4, true);
		}
	}
};

#endif
