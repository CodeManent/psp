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
	bool condition = (cpu.SGPR[u.i.rs] > 0);
	if(condition){
		const int32 target = cpu.PC + expandOffset();
		changePC(cpu, target + 4);
	}
}
