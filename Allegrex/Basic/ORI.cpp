#include "ORI.h"
#include "../Allegrex.h"
#include <sstream>

ORI::ORI(const uint32 inst): Instruction(inst)
{
}

ORI::~ORI(void)
{
}

std::string ORI::disassemble() const{
	std::stringstream ss;

	ss << "ori\t" << strRt() << ", " << strRs() << ", " << strHexImmediate();

	return ss.str();
}

void ORI::execute(Allegrex &cpu) const{
	cpu.GPR[u.i.rt] = (cpu.GPR[u.i.rs] | static_cast<const uint32>(u.i.immediate));
}
