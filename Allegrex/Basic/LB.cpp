#include "LB.h"
#include "../Allegrex.h"

LB::LB(const uint32 inst): Instruction(inst)
{
}

LB::~LB(void)
{
}

std::string LB::disassemble() const{
	std::stringstream ss;

	ss << "lb\t" << strRt() << ", " << strOffset() << "(" << strRs()  << ")";

	return ss.str();
}

void LB::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & ~3);
	const uint32 byte = vAddr & 3;
	const uint8 data = (mem >> (8*byte)) & 0xff;
	cpu.SGPR[u.i.rt] = static_cast<int32>(static_cast<int8>(data));
}
