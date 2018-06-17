#ifndef SYSCALL_H_
#define SYSCALL_H_
#pragma once

#include "../Instruction.h"
#include <iomanip>

/*********************************************************************** p.A-118
 * SYSCALL rs, rt
 *
 */
class SYSCALL :
	public Instruction
{
public:
	SYSCALL(const uint32 inst):Instruction(inst){}
	virtual ~SYSCALL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << std::hex<< std::setfill('0') 
			<< "syscall 0x" << std::setw(5) << ((inst >> 6) & 0x000fffff);

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.systemCoprocessor.raiseException(COP0::SYS);
	}
};

#endif

