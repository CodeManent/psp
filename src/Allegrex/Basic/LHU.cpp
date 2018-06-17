#include "LHU.h"
#include "../Allegrex.h"

LHU::LHU(const uint32 inst): Instruction(inst)
{
}

LHU::~LHU(void)
{
}

std::string LHU::disassemble() const{
	std::stringstream ss;

	ss << "lhu\t" << strRt() << ", " << strOffset() << "(" << strRs()  << ")";

	return ss.str();
}

void LHU::execute(Allegrex &cpu) const{
	const uint32 vAddr = (signExtendImm() + cpu.GPR[u.i.rs]);
	// mask out the 2nd bit so not to cause address error based on it
	// error on the last bit
	const uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr & ~2);
	const uint32 byte = vAddr & 3;
	const uint16 data = (mem >> (8*byte)) & 0xffff;
	cpu.GPR[u.i.rt] = static_cast<uint32>(data);
}
