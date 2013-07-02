#include "JALR.h"
#include "../Allegrex.h"
#include <sstream>

JALR::JALR(const uint32 inst):Instruction(inst)
{
}

JALR::~JALR()
{
}

std::string JALR::disassemble() const{
	std::stringstream ss;

	if(u.r.rd == 31)
		ss << "jalr\t" << strRs();
	else
		ss << "jalr\t" << strRd() << ", " << strRs();

	return ss.str();
}

void JALR::execute(Allegrex &cpu) const{
	const uint32 temp = cpu.GPR[u.r.rs];
	cpu.GPR[u.r.rd] = cpu.PC + 8;
	cpu.PC = temp;
}
