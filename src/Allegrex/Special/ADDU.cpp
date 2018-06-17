#include "ADDU.h"
#include "../Allegrex.h"
#include <sstream>

ADDU::ADDU(const uint32 inst):Instruction(inst)
{
}

ADDU::~ADDU(void)
{
}

std::string ADDU::disassemble() const{
	std::stringstream ss;

	ss << "addu\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void ADDU::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs] + cpu.GPR[u.r.rt];
}
