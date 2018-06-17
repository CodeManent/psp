#ifndef BLTZAL_H_
#define BLTZAL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-35
 * Branch On Less Than Zero And Link
 *
 * BLTZAL rs, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. Unconditionally, the address of the instruction after the
 * delay slot is placed in the link register, r31. If the contents of general
 * register rs have the sign bit set, then the program branches to the target
 * address, with a delay of one instruction.
 *
 * General register rs may not be general register 31, because such an
 * instruction is not restartable. An attempt to execute this instruction with
 * register 31 specified as rs is not trapped however.
 */
class BLTZAL :
	public Instruction
{
public:
	BLTZAL(const uint32 inst):Instruction(inst){}
	virtual ~BLTZAL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bltzal\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// TODO: static assert
		static_assert(Allegrex::ra == 31, "Allegrex::ra is not 31");
		cpu.GPR[Allegrex::ra] = cpu.PC + 8;
		// bool condition = (cpu.SGPR[u.i.rs] < 0);
		// grt the sign bit
		bool condition = cpu.GPR[u.i.rs] & 0x80000000;
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4);
		}
	}
};

#endif
