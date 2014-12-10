#include "LWL.h"
#include "../Allegrex.h"
#include <sstream>

LWL::LWL(const uint32 inst): Instruction(inst)
{
}

LWL::~LWL(void)
{
}

std::string LWL::disassemble() const{
	std::stringstream ss;

	ss << "lwl\t" << strRt() << ", " << strRs() << "(" << strSignedImmediate()  << ")";

	return ss.str();
}

void LWL::execute(Allegrex &cpu) const{
	// TODO: check correctness
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 mask = ~(0x03);
	auto byte = vAddr & ~mask;

	uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & mask);

	mem <<= byte;
	cpu.GPR[u.i.rt] |= mem;
}
