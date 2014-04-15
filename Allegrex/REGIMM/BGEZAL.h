#ifndef BGEZAL_H_
#define BGEZAL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-28
 * Branch On Greater Than Or Equal To Zero And Link
 *
 * BGEZAL rs, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. Uncoditionally, the address of the instruction after the delay
 * slot is placed in the link register r31. If the contents of general register
 * rs have the sign bit cleared, then the program branches to the target
 * address, with a delay of one instruction.
 *

 */
class BGEZAL :
	public Instruction
{
public:
	BGEZAL(const uint32 inst):Instruction(inst){}
	virtual ~BGEZAL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bgezal\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		cpu.GPR[31] = cpu.PC + 8;
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
