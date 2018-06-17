#ifndef BGEZ_H_
#define BGEZ_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-35
 * Branch On Greater Than Or Equal To Zero
 *
 * BGEZ rs, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. The contents of general register rs have the sign bit cleared,
 * then the program branches to the target address, with a delay of one
 * instruction.
 */
class BGEZ :
	public Instruction
{
public:
	BGEZ(const uint32 inst):Instruction(inst){}
	virtual ~BGEZ(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bgez\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// bool condition = (cpu.SGPR[u.i.rs] >= 0);
		// get the sign bit
		bool condition = (cpu.GPR[u.i.rs] & 0x80000000) == 0;
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4);
		}
	}
};

#endif
