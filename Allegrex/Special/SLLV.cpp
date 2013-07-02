#include "SLLV.h"
#include "../Allegrex.h"
#include <sstream>

SLLV::SLLV(const uint32 inst):Instruction(inst)
{
}

SLLV::~SLLV(void)
{
}

std::string SLLV::disassemble() const{
	std::ostringstream oss;

	oss << "sllv\t" << strRd() << ", " << strRt() << ", " << strRs();

	return oss.str();
}

void SLLV::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = (cpu.GPR[u.r.rt] << (cpu.GPR[u.r.rs] & 0x0000001F));
}
