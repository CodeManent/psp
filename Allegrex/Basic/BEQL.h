#ifndef BEQL_H_
#define BEQL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/************************************************************************ p.A-26
 * BEQL rs, rt, offset
 *
 * A branch target address is computed from the sum of the adress of the
 * instruction in the delay slot and the 16-bit offset, shifted left two bits
 * and sign extended. The contents of general register rs and the contents of
 * general register rt are compared. If the two registers are equal, the target
 * address is branched to, with a delay of one instruction. If the conditional
 * branch is not taken, the instruction in the branch delay slot is nullified.
 *
 * target ← (offset_15)^14 || offset || 00
 * condition ← (GPR[rs] = GPR[rt])
 * if condition then
 *     PC ← PC + target
 * else
 *     Nullify current instruction
 * endif
 */
class BEQL :
	public Instruction
{
public:
	BEQL(const uint32 inst):Instruction(inst){};
	virtual ~BEQL(void){};

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "beql\t" << strRs() << ", " << strRt() << ", " << strOffset();

		return ss.str();
	}
	virtual void execute(Allegrex &cpu) const{
		bool condition = (cpu.GPR[u.i.rs] == cpu.GPR[u.i.rt]);
		if(condition){
			// + 4 because the target address is computed based on the PC of
			// the delay slot.
			const int32 target = cpu.PC +  expandOffset();
			changePC(cpu, target + 4, true);
		}
	}
};

#endif
