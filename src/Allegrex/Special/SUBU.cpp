#include "SUBU.h"
#include "../Allegrex.h"
#include <sstream>

SUBU::SUBU(const uint32 inst):Instruction(inst)
{
}

SUBU::~SUBU(void)
{
}

std::string SUBU::disassemble() const{
	std::stringstream ss;

	ss << "subu\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void SUBU::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs] - cpu.GPR[u.r.rt];
}
