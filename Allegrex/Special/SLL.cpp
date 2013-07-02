#include "SLL.h"
#include "../Allegrex.h"
#include <sstream>

SLL::SLL(const uint32 inst):Instruction(inst)
{
}

SLL::~SLL(void)
{
}

std::string SLL::disassemble() const{
	std::ostringstream oss;

	oss << "sll\t" << strRd() << ", " << strRt() << ", " << strSa();

	return oss.str();
}

void SLL::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = cpu.GPR[u.r.rt] << u.r.sa;
}
