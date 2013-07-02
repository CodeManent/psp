#include "ADDI.h"
#include "../Allegrex.h"
#include <sstream>

ADDI::ADDI(const uint32 inst):Instruction(inst)
{
}

ADDI::~ADDI(void)
{
}

std::string ADDI::disassemble() const{
	std::stringstream ss;

	ss << "addi\t" << strRt() << ", " <<  strRs() << ", " << strSignedImmediate();

	return ss.str();
}

void ADDI::execute(Allegrex &cpu) const{
	const int32 signExtended = static_cast<const int32>(static_cast<const int16>(u.i.immediate));

	if(additionOverflows(cpu.SGPR[u.r.rs], signExtended)){
		//raise integer overflow exception
		TODO("raise integer overflow exception")

	}

	cpu.SGPR[u.i.rt] = cpu.SGPR[u.i.rs] + signExtended;
}
