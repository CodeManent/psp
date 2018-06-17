#include "SB.h"
#include "../Allegrex.h"
#include <sstream>

SB::SB(const uint32 inst):Instruction(inst)
{
}

SB::~SB(void)
{
}
std::string SB::disassemble() const{
	std::stringstream ss;

	ss << "sb\t" << strRt() << ", " << strOffset() << '(' << strRs() << ')';

	return ss.str();
}

void SB::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	// TODO: check is is is correct or if it affects only one byte
	const uint32 data =  (cpu.GPR[u.i.rt] & 0xff) << (vAddr & 3);
	cpu.systemCoprocessor.writeMemory(vAddr, data);
}

