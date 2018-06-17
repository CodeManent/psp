#include "BNE.h"
#include "../Allegrex.h"
#include <sstream>

BNE::BNE(const uint32 inst):Instruction(inst)
{
}

BNE::~BNE(void)
{
}

std::string BNE::disassemble() const{
	std::stringstream ss;

	ss << "bne\t" << strRs() << ", " << strRt() << ", " << strOffset();

	return ss.str();
}

void BNE::execute(Allegrex &cpu) const{
	bool condition = (cpu.GPR[u.i.rs] != cpu.GPR[u.i.rt]);
	if(condition){
		const uint32 target = cpu.PC + expandOffset();
		jump(cpu, target + 4);
	}
}

