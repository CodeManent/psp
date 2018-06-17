#include "LWR.h"
#include "../Allegrex.h"
#include <sstream>

LWR::LWR(const uint32 inst): Instruction(inst)
{
}

LWR::~LWR(void)
{
}

std::string LWR::disassemble() const{
	std::stringstream ss;

	ss << "lwr\t" << strRt() << ", " << strSignedImmediate() << '(' << strRs() << ')';

	return ss.str();
}

void LWR::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 mask = ~(0x03);
	auto byte = vAddr & ~mask;

	uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & mask);

	const uint32 shift = byte * 8;
	mem >>= shift;
	const uint32 writemask = (0xFFFFFFFF >> shift);
	cpu.GPR[u.i.rt] &= ~writemask;
	cpu.GPR[u.i.rt] |= mem;
}

