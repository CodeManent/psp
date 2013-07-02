#include "SLTIU.h"
#include "../Allegrex.h"
#include <sstream>

SLTIU::SLTIU(const uint32 inst):Instruction(inst)
{
}

SLTIU::~SLTIU(void)
{
}

std::string SLTIU::disassemble()const{
	std::stringstream ss;

	ss << "sltiu\t" << strRt() << ", " << strRs() << ", " << strUnsignedImmediate();

	return ss.str();
}

void SLTIU::execute(Allegrex &cpu) const{
	const uint32 signExtended = static_cast<const uint32>(static_cast<const int32>(static_cast<const int16>(u.i.immediate)));

	cpu.GPR[u.i.rt] = (cpu.GPR[u.i.rs] < signExtended);
}
