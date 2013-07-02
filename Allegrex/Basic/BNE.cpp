#include "BNE.h"
#include "../Allegrex.h"
#include <sstream>

BNE::BNE(const uint32 inst):Instruction(inst)
{
}

BNE::~BNE(void)
{
}

std::string BNE::disassemble() const{
	std::stringstream ss;

	ss << "bne\t" << strRs() << ", " << strRt() << ", " << strOffset();

	return ss.str();
}

void BNE::execute(Allegrex &cpu) const{
	const int32 target = static_cast<const int32>(static_cast<const int16>(u.i.immediate)) << 2;
	bool condition = (cpu.GPR[u.i.rs] != cpu.GPR[u.i.rt]);
	if(condition){
		cpu.PC += target;
	}
}
