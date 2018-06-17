#include "LUI.h"
#include "../Allegrex.h"
#include <sstream>

LUI::LUI(const uint32 inst): Instruction(inst)
{
}

LUI::~LUI(void)
{
}

std::string LUI::disassemble() const{
	std::stringstream ss;

	ss << "lui\t" << strRt() << ", " << strHexImmediate();

	return ss.str();
}

void LUI::execute(Allegrex &cpu) const{
	cpu.GPR[u.i.rt] = static_cast<const uint32>(u.i.immediate) << 16;
}
