#include "NOR.h"
#include "../Allegrex.h"
#include <sstream>

NOR::NOR(const uint32 inst): Instruction(inst)
{
}

NOR::~NOR(void)
{
}

std::string NOR::disassemble() const{
	std::stringstream ss;

	ss << "nor\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}


void NOR::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = ~(cpu.GPR[u.r.rs] | cpu.GPR[u.r.rt]);
}
