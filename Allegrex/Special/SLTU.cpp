#include "SLTU.h"
#include "../Allegrex.h"
#include <sstream>

SLTU::SLTU(const uint32 inst):Instruction(inst)
{
}

SLTU::~SLTU(void)
{
}

std::string SLTU::disassemble() const{
	std::stringstream ss;

	ss << "sltu\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void SLTU::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = (cpu.GPR[u.r.rs] < cpu.GPR[u.r.rt]);
}
