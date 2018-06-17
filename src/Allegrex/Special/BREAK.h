#ifndef BREAK_H_
#define BREAK_H_
#pragma once

#include "../Instruction.h"
#include <iomanip>

/*********************************************************************** p.A-118
 * BREAK rs, rt
 *
 */
class BREAK :
	public Instruction
{
public:
	BREAK(const uint32 inst):Instruction(inst){}
	virtual ~BREAK(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << std::hex<< std::setfill('0') 
			<< "break 0x" << std::setw(5) << ((inst >> 6) & 0x000fffff);

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		cpu.systemCoprocessor.raiseException(COP0::Bp);
	}
};

#endif

