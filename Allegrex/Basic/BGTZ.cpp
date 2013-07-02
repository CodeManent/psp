#include "BGTZ.h"
#include "../Allegrex.h"
#include <sstream>

BGTZ::BGTZ(const uint32 inst): Instruction(inst)
{
}

BGTZ::~BGTZ(void)
{
}

std::string BGTZ::disassemble() const{
	std::stringstream ss;

	ss << "bgtz\t" << strRs() << ", " << strOffset();

	return ss.str();
}

void BGTZ::execute(Allegrex &cpu) const{
	const int32 target = static_cast<const int32>(static_cast<const int16>(u.i.immediate)) << 2;
	//bool condition = ((cpu.GPR[u.i.rs] &0x80000000) == 0x00000000) || (cpu.GPR[u.i.rt] != 0);
	bool condition = static_cast<int32>(cpu.GPR[u.i.rs]) > 0;
	if(condition){
		cpu.PC += target;
	}
}
