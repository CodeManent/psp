#ifndef BLTZL_H_
#define BLTZL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/*********************************************************************** p. A-35
 * Branch On Less Than Zero Likely
 *
 * BLTZL rs, offset
 *
 * A branch target address is computed from the sum of the address of the
 * instruction in the delay slot and the 16bit offset, shifted left two bits and
 * sign-extended. The contents of general register rs have the sign bit set,
 * then the program branches to the target address, with a delay of one
 * instruction.
 */
class BLTZL :
	public Instruction
{
public:
	BLTZL(const uint32 inst):Instruction(inst){}
	virtual ~BLTZL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "bltzl\t" << strRs() << ", " << strOffset();
		return ss.str();
	}

	virtual void execute(Allegrex &cpu) const{
		// bool condition = (cpu.SGPR[u.i.rs] < 0);
		// grt the sign bit
		bool condition = cpu.GPR[u.i.rs] & 0x80000000;
		if(condition){
			const uint32 target = cpu.PC + expandOffset();
			jump(cpu, target + 4, true);
		}
	}
};

#endif
