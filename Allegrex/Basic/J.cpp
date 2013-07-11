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
	cpu.PC = findTarget(cpu.PC + 4);
}
