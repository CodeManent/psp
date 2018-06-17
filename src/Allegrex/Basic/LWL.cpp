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

	ss << "lwl\t" << strRt() << ", " << strSignedImmediate() << '(' << strRs() << ')';

	return ss.str();
}

void LWL::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 mask = ~(0x03);
	auto byte = vAddr & ~mask;

	uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & mask);

	const uint32 shift = (3 - byte) * 8;
	const uint32 writemask = (0xFFFFFFFF << shift);

	mem <<= shift;
	cpu.GPR[u.i.rt] &= ~writemask;
	cpu.GPR[u.i.rt] |= mem;
}

