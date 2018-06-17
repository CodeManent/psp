#include "SWL.h"
#include "../Allegrex.h"
#include <sstream>

SWL::SWL(const uint32 inst): Instruction(inst)
{
}

SWL::~SWL(void)
{
}

std::string SWL::disassemble() const{
	std::stringstream ss;

	ss << "swl\t" << strRt() << ", " << strSignedImmediate() << '(' << strRs() << ')';

	return ss.str();
}

void SWL::execute(Allegrex &cpu) const{
	// TODO: fix implementation to match description and checkfor correctness.
	// now instead of pushing just the actual bytes into the memory subsystem
	// we load the word, process it and write it back.
	const uint32 effAddr = signExtendImm() + cpu.GPR[u.i.rs];
	const uint32 addrMask = ~(0x03);
	auto byte = effAddr & ~addrMask;

	uint32 word = cpu.systemCoprocessor.loadMemory32(effAddr & addrMask);

	const uint32 shift = (3-byte) * 8;
	const uint32 writeMask = (0xFFFFFFFF >> shift);

	const uint32 modifiedRegister = cpu.GPR[u.i.rt] >> shift;

	cpu.systemCoprocessor.writeMemory(
	/*addr*/effAddr & addrMask,
	/*data*/(word & ~writeMask) | (modifiedRegister & writeMask));
}

