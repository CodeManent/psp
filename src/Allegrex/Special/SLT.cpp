#include "SLT.h"
#include "../Allegrex.h"
#include <sstream>

SLT::SLT(const uint32 inst): Instruction(inst)
{
}

SLT::~SLT(void)
{
}

std::string SLT::disassemble() const{
	std::stringstream ss;

	ss << "slt\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}


void SLT::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = (cpu.SGPR[u.r.rs] < cpu.SGPR[u.r.rt]);
}
