#include "SLTI.h"
#include "../Allegrex.h"
#include <sstream>

SLTI::SLTI(const uint32 inst):Instruction(inst)
{
}

SLTI::~SLTI(void)
{
}
std::string SLTI::disassemble() const{
	std::stringstream ss;

	ss << "slti\t" << strRt() << ", " << strRs() << ", " << strSignedImmediate();

	return ss.str();
}

void SLTI::execute(Allegrex &cpu) const{
	const int32 signExtended = static_cast<const int32>(static_cast<const int16>(u.i.immediate));

	cpu.GPR[u.i.rt] = (cpu.SGPR[u.i.rs] < signExtended);
}
