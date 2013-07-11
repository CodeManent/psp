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
	const int32 target = expandOffset(u.i.immediate);
	bool condition = (cpu.SGPR[u.i.rs] <= 0);
	if(condition){
		changePC(cpu, target +4);
	}
}
