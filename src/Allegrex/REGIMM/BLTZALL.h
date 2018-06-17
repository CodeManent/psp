#ifndef BLTZALL_H_
#define BLTZALL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-37
 * Branch On Less Than Zero And Link Likely
 *
 * BLTZALL rs, offset
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
 *
 * If the conditional branch is not taken, the instructino in the delay slot
 * is nullified
 */
class BLTZALL :
	public Instruction
{
public:
	BLTZALL(const uint32 inst):Instruction(inst){}
	virtual ~BLTZALL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bltzall\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		static_assert(Allegrex::ra == 31, "Allegrex::ra is not 31");
		cpu.GPR[Allegrex::ra] = cpu.PC + 8;
		// bool condition = (cpu.SGPR[u.i.rs] < 0);
		// grt the sign bit
		bool condition = (cpu.GPR[u.i.rs] & 0x80000000) == 0x80000000;
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4, true);
		}
	}
};

#endif

