#include "LW.h"
#include "../Allegrex.h"
#include <sstream>

LW::LW(const uint32 inst): Instruction(inst)
{
}

LW::~LW(void)
{
}

std::string LW::disassemble() const{
	std::stringstream ss;

	ss << "lw\t" << strRt() << ", " << strRs() << "(" << strOffset()  << ")";

	return ss.str();
}

void LW::execute(Allegrex &cpu) const{
	TODO("proper implementation")
	const uint32 vAddr = static_cast<int32>(static_cast<uint32>(u.i.immediate)) + cpu.GPR[u.i.rs];
//	uint32 pAddr = AddressTranslation(vAddr, DATA);
//	pAddr &= 0xfffffffC;
//	uint32 mem = loadMemory(uncached, WORD, pAddr, vAddr, DATA);
//	cpu.GPR[u.i.rt] = mem;
	uint32 mem = cpu.systemCoprocessor.loadMemory32(vAddr);
	cpu.GPR[u.i.rt] = mem;
}
