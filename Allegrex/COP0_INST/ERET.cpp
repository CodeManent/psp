#include "ERET.h"
#include "../Allegrex.h"
#include "../COP0.h"

ERET::ERET(uint32 inst)
:Instruction(inst)
{
}

std::string ERET::disassemble() const
{
	std::stringstream ss;
	ss << "eret";
	return ss.str();
}

void ERET::execute(Allegrex &cpu) const
{
	auto statusReg = cpu.systemCoprocessor.getReg(COP0::Status);
	const uint32 ERLMask = 0x00000004;
	const uint32 EXLMask = 0x00000002;

	if((statusReg & ERLMask) == ERLMask){
		cpu.PC = cpu.systemCoprocessor.getReg(COP0::ErrorEPC);
		// cpu.systemCoprocessor.statusReg.ERL = 0;
		// clear the ERL bit
		statusReg &= ~ERLMask;
	}
	else{
		cpu.PC = cpu.systemCoprocessor.getReg(COP0::EPC);
		// cpu.systemCoprocessor.statusReg.EXL = 0;
		statusReg &= ~EXLMask;
	}
	cpu.systemCoprocessor.setReg(COP0::Status, statusReg);
	
	// and break the LL/SC chain
	cpu.systemCoprocessor.LLbit = 0;
}
