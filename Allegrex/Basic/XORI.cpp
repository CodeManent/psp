#include "XORI.h"
#include "../Allegrex.h"
#include <sstream>

XORI::XORI(const uint32 inst): Instruction(inst)
{
}

XORI::~XORI(void)
{
}

std::string XORI::disassemble() const{
	std::stringstream ss;

	ss << "xori\t" << strRt() << ", " << strRs() << ", " << strHexImmediate();

	return ss.str();
}

void XORI::execute(Allegrex &cpu) const{
	cpu.GPR[u.i.rt] = (cpu.GPR[u.i.rs] ^ static_cast<const uint32>(u.i.immediate));
}
