#ifndef BLEZL_H_
#define BLEZL_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

class BLEZL :
	public Instruction
{
public:
	BLEZL(const uint32 inst):Instruction(inst){}
	virtual ~BLEZL(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;
		ss << "blezl\t" << strRs() << ", " << strOffset();
		return ss.str();
	}
	virtual void execute(Allegrex &cpu) const{
		const int32 target = expandOffset(u.i.immediate);
		bool condition = (cpu.SGPR[u.i.rs] <= 0);
		if(condition){
			changePC(cpu, target + 4, true);
		}
	}
};

#endif

