#include "BEQ.h"
#include "../Allegrex.h"
#include <sstream>

BEQ::BEQ(const uint32 inst):Instruction(inst)
{
}

BEQ::~BEQ(void)
{
}

std::string BEQ::disassemble()const{
	std::stringstream ss;

	ss << "beq\t" << strRs() << ", " << strRt() << ", " << strOffset();

	return ss.str();
}

void BEQ::execute(Allegrex &cpu) const{
	const int32 target = static_cast<const int32>(static_cast<const int16>(u.i.immediate)) << 2;
	bool condition = (cpu.GPR[u.i.rs] == cpu.GPR[u.i.rt]);
	if(condition){
		cpu.PC += target;
	}
}
