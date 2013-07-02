#include "XOR.h"
#include "../Allegrex.h"
#include <sstream>

XOR::XOR(const uint32 inst): Instruction(inst)
{
}

XOR::~XOR(void)
{
}

std::string XOR::disassemble() const{
	std::stringstream ss;

	ss << "xor\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void XOR::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rs] ^ cpu.GPR[u.r.rt];
}
