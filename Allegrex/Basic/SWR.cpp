#include "SWR.h"
#include "../Allegrex.h"
#include <sstream>

SWR::SWR(const uint32 inst): Instruction(inst)
{
}

SWR::~SWR(void)
{
}

std::string SWR::disassemble() const{
	std::stringstream ss;

	ss << "swr\t" << strRt() << ", " << strSignedImmediate() << '(' << strRs() << ')';

	return ss.str();
}

void SWR::execute(Allegrex &cpu) const{
	//SWL implementation follows
	// TODO: fix implementation to match description and checkfor correctness.
	//       the same as SWL
	const uint32 effAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 addrMask = ~(0x03);
	auto byte = effAddr & ~addrMask;

	uint32 word = cpu.systemCoprocessor.loadMemory32(effAddr & addrMask);

	const uint32 shift = byte * 8;
	const uint32 writeMask = (0xFFFFFFFF << shift);

	const uint32 modifiedRegister = cpu.GPR[u.i.rt] << shift;

	cpu.systemCoprocessor.writeMemory(
	/*addr*/effAddr & addrMask,
	/*data*/(word & ~writeMask) | (modifiedRegister & writeMask));
}

