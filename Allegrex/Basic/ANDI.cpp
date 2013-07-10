#include "ANDI.h"
#include "../Allegrex.h"
#include <sstream>

ANDI::ANDI(const uint32 inst): Instruction(inst)
{
}

ANDI::~ANDI(void)
{
}

std::string ANDI::disassemble() const{
	std::stringstream ss;

	ss << "andi\t" << strRt() << ", " << strRs() << ", " << strHexImmediate();

	return ss.str();
}

void ANDI::execute(Allegrex &cpu) const{
	TODO("check zero extend")
	cpu.GPR[u.i.rt] = (cpu.GPR[u.i.rs] & static_cast<const uint32>(u.i.immediate));
}
