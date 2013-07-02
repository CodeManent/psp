#include "BLEZ.h"
#include "../Allegrex.h"
#include <sstream>

BLEZ::BLEZ(const uint32 inst):Instruction(inst)
{
}

BLEZ::~BLEZ(void)
{
}

std::string BLEZ::disassemble() const{
	std::stringstream ss;

	ss << "blez\t" << strRs() << ", " << strOffset();

	return ss.str();
}

void BLEZ::execute(Allegrex &cpu) const{
	const int32 target = static_cast<const int32>(static_cast<const int16>(u.i.immediate)) << 2;
	bool condition = ((cpu.GPR[u.i.rs] &0x80000000) == 0x80000000) || (cpu.GPR[u.i.rt] == 0);
	if(condition){
		cpu.PC += target;
	}
}
