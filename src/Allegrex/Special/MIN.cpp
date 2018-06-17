#include "MIN.h"
#include "../Allegrex.h"
#include <sstream>
#include <algorithm> // for min

// TODO: Verify MIN implementation

MIN::MIN(const uint32 inst):Instruction(inst)
{
}

MIN::~MIN(void)
{
}

std::string MIN::disassemble() const{
	std::stringstream ss;

	ss << "min\t" << strRd() << ", " << strRs() << ", " << strRt();

	return ss.str();
}

void MIN::execute(Allegrex &cpu) const{
	cpu.GPR[u.r.rd] = std::min(cpu.GPR[u.r.rs] , cpu.GPR[u.r.rt]);
}
