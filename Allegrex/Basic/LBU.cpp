#include "LBU.h"
#include "../Allegrex.h"

LBU::LBU(const uint32 inst): Instruction(inst)
{
}

LBU::~LBU(void)
{
}

std::string LBU::disassemble() const{
	std::stringstream ss;

	ss << "lbu\t" << strRt() << ", " << strOffset() << "(" << strRs()  << ")";

	return ss.str();
}

void LBU::execute(Allegrex &cpu) const{
	const uint32 vAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & ~3);
	const uint32 byte = vAddr & 3;
	const uint8 data = (mem >> (8*byte)) & 0xff;
	cpu.GPR[u.i.rt] = static_cast<uint32>(data);
}
