#ifndef SUB_H_
#define SUB_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/********************************************************************** p.A-150
 * SUB rd, rs, rt
 *
 * The 32-bit word value in GPR rt is subtracted fron the 32bit value in GPR rs
 * to produce a 32bit result. Is the subtraction results in 32bit 2's complement
 * arithmetic overflow, then the destination register is not modified and an
 * integer overflow exceprion occurs. If it does not overflow, the 32bit result
 * id places into GPR rs.
 */
class SUB :
	public Instruction
{
public:
	SUB(const uint32 inst):Instruction(inst){}
	virtual ~SUB(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "sub\t" << strRd() << ", " << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		if(additionOverflows(cpu.SGPR[u.r.rs], -cpu.SGPR[u.r.rt]))
			cpu.systemCoprocessor.raiseException(COP0::Ov);

		cpu.SGPR[u.r.rd] = cpu.SGPR[u.r.rs] - cpu.SGPR[u.r.rt];
	}
};

#endif
