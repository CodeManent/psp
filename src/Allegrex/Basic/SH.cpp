#include "SH.h"
#include "../Allegrex.h"
#include <sstream>

SH::SH(const uint32 inst):Instruction(inst)
{
}

SH::~SH(void)
{
}
std::string SH::disassemble() const{
	std::stringstream ss;

	ss << "sb\t" << strRt() << ", " << strOffset() << '(' << strRs() << ')';

	return ss.str();
}

void SH::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	// TODO: check if it is correct or if it should affect only 2 bytes
	const uint32 data =  (cpu.GPR[u.i.rt] & 0xffff) << (vAddr & 3);
	cpu.systemCoprocessor.writeMemory(vAddr, data);
}

