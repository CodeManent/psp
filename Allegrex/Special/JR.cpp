#include "JR.h"
#include "../Allegrex.h"

#include <sstream>

JR::JR(const uint32 inst): Instruction(inst)
{
}

JR::~JR(void)
{
}

std::string JR::disassemble() const{
	std::stringstream ss;

	ss << "jr\t" << strRs();

	return ss.str();
}

void JR::execute(Allegrex &cpu) const{
	changePC(cpu, cpu.GPR[u.r.rs]);
}
