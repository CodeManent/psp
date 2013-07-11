#include "JAL.h"
#include "../Allegrex.h"

#include <sstream>


JAL::JAL(const uint32 inst):Instruction(inst)
{
}

JAL::~JAL(void)
{
}

std::string JAL::disassemble() const{
	std::stringstream ss;

	ss << "jal\t" << strTarget();

	return ss.str();
}

void JAL::execute(Allegrex &cpu) const{
	cpu.GPR[31] = cpu.PC + 8;
	cpu.PC = findTarget(cpu.PC + 4);
}
