#include "LW.h"
#include "../Allegrex.h"
#include <sstream>

LW::LW(const uint32 inst): Instruction(inst)
{
}

LW::~LW(void)
{
}

std::string LW::disassemble() const{
	std::stringstream ss;

	ss << "lw\t" << strRt() << ", " << strRs() << "(" << strOffset()  << ")";

	return ss.str();
}

void LW::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr);
	cpu.GPR[u.i.rt] = mem;
}
