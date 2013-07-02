#include "OR.h"
#include "../Allegrex.h"
#include <sstream>

OR::OR(const uint32 inst): Instruction(inst)
{
}

OR::~OR(void)
{
}

std::string OR::disassemble() const{
	std::stringstream ss;

	ss << "or\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void OR::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs] & cpu.GPR[u.r.rt];
}
