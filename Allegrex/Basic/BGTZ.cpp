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
	const int32 target = expandOffset();
	bool condition = (cpu.SGPR[u.i.rs] > 0);
	if(condition){
		changePC(cpu, target + 4);
	}
}
