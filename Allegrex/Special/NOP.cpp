#include "NOP.h"

NOP::NOP(void):Instruction(0)
{
}

NOP::~NOP(void)
{
}

std::string NOP::disassemble() const{
	return "nop";
}

void NOP::execute(Allegrex &) const{
}
