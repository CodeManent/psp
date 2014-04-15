#include "SW.h"
#include "../Allegrex.h"
#include <sstream>
#include <stdexcept>

SW::SW(const uint32 inst):Instruction(inst)
{
}

SW::~SW(void)
{
}
std::string SW::disassemble() const{
	std::stringstream ss;

	ss << "sw\t" << strRt() << ", " << strOffset() << '(' << strRs() << ')';

	return ss.str();
}

void SW::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	cpu.systemCoprocessor.writeMemory(vAddr, cpu.GPR[u.i.rt]);
}
