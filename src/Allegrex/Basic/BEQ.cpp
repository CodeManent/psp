#include "BEQ.h"
#include "../Allegrex.h"
#include <sstream>

BEQ::BEQ(const uint32 inst):Instruction(inst)
{
}

BEQ::~BEQ(void)
{
}

std::string BEQ::disassemble()const{
	std::stringstream ss;

	ss << "beq\t" << strRs() << ", " << strRt() << ", " << strOffset();

	return ss.str();
}

void BEQ::execute(Allegrex &cpu) const{
	bool condition = (cpu.GPR[u.i.rs] == cpu.GPR[u.i.rt]);
	if(condition){
		const int32 target = cpu.PC + expandOffset();
		// + 4 because the target is computed based on the PC of the delay slot.
		jump(cpu, target+4);
	}
}
