#include "LH.h"
#include "../Allegrex.h"

LH::LH(const uint32 inst): Instruction(inst)
{
}

LH::~LH(void)
{
}

std::string LH::disassemble() const{
	std::stringstream ss;

	ss << "lh\t" << strRt() << ", " << strOffset() << "(" << strRs()  << ")";

	return ss.str();
}

void LH::execute(Allegrex &cpu) const{
	const uint32 vAddr = (signExtendImm() + cpu.GPR[u.i.rs]);
	// maks out the 2nd bit so not to cause address error based on it
	// error on the last bit
	const uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & ~2);
	const uint32 byte = vAddr & 3;
	const uint16 data = (mem >> (8*byte)) & 0xffff;
	cpu.SGPR[u.i.rt] = static_cast<int32>(static_cast<int16>(data));
}
