#include "J.h"
#include "../Allegrex.h"
#include <sstream>

J::J(const uint32 inst):Instruction(inst)
{
}

J::~J(void)
{
}

std::string J::disassemble() const{
	std::ostringstream oss;

	oss << "j\t" << strTarget();

	return oss.str();
}

void J::execute(Allegrex &cpu) const{
	cpu.PC = (cpu.PC & 0xF0000000) | (u.j.target << 2);
}
