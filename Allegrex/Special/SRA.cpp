#include "SRA.h"
#include "../Allegrex.h"

SRA::SRA(const uint32 inst): Instruction(inst)
{
}

SRA::~SRA(void)
{
}

std::string SRA::disassemble() const{
	std::stringstream ss;

	ss << "sra\t" << strRd() << ", " << strRt() << ", " << strSa();

	return ss.str();
}

void SRA::execute(Allegrex &cpu) const{
	cpu.SGPR[u.r.rd] = cpu.SGPR[u.r.rt] >> u.r.sa;
}
