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
	const int32 signExtended = signExtendImm();

	if(additionOverflows(cpu.SGPR[u.i.rs], signExtended)){
		cpu.systemCoprocessor.raiseException(COP0::Ov);
	}

	cpu.SGPR[u.i.rt] = cpu.SGPR[u.i.rs] + signExtended;
}
