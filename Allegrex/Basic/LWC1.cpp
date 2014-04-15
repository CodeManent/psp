#include "LWC1.h"
#include "../Allegrex.h"
#include <sstream>

LWC1::LWC1(const uint32 inst): Instruction(inst)
{
}

LWC1::~LWC1(void)
{
}

std::string LWC1::disassemble() const{
	std::stringstream ss;

	ss << "lwc1\t" << strRt() << ", " << strRs() << "(" << strSignedImmediate()  << ")";

	return ss.str();
}

void LWC1::execute(Allegrex &cpu) const{
	(void)cpu;//suppress unused parameter warning. TODO: use or remove parameter
	throw std::logic_error("Unfinished implementation fot instruction LWC1. No Coprocessor 1 exists yes");
	//const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	//const uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr);
	// TODO: finish implementation after the inclusion of coprocessor 1.
	//setReg(u.rt, mem);
}
