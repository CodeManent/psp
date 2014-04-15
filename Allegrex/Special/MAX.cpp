#include "MAX.h"
#include "../Allegrex.h"
#include <sstream>

// TODO: Verify max implementation

MAX::MAX(const uint32 inst):Instruction(inst)
{
}

MAX::~MAX(void)
{
}

std::string MAX::disassemble() const{
	std::stringstream ss;

	ss << "max\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void MAX::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = std::max(cpu.GPR[u.r.rs] , cpu.GPR[u.r.rt]);
}
