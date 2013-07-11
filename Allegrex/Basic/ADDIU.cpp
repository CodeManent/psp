#include "ADDIU.h"
#include "../Allegrex.h"
#include <sstream>

ADDIU::ADDIU(const uint32 inst):Instruction(inst)
{
}

ADDIU::~ADDIU(void)
{
}

std::string ADDIU::disassemble() const{
	std::stringstream ss;

	ss << "addiu\t" << strRt() << ", " << strRs() << ", " << strUnsignedImmediate();

	return ss.str();
}

void ADDIU::execute(Allegrex &cpu)const{
	const uint32 signExtended = signExtendImm();

	cpu.GPR[u.i.rt] = cpu.GPR[u.r.rs] + signExtended;
}
