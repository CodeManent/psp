#include "AND.h"
#include "../Allegrex.h"
#include <sstream>

AND::AND(const uint32 inst):Instruction(inst)
{
}

AND::~AND(void)
{
}

std::string AND::disassemble() const{
	std::stringstream ss;

	ss << "and\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void AND::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs] & cpu.GPR[u.r.rt];
}
