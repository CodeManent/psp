#ifndef ADD_H_
#define ADD_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/************************************************************************ p.A-11
 * ADD rd, rs, rt
 *
 * The contents of the general register sr and the contents of the general
 * register rt are added to form the result. The result is placed into general
 * register rd.
 *
 * An overflow exception occurs if the carries out of bits 30 nd 31 differ
 * (2s complement overflow). The destinatino register rd is not modified when
 * an integer overflow exception occurs.
 */
class ADD :
	public Instruction
{
public:
	ADD(const uint32 inst):Instruction(inst){}
	virtual ~ADD(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "add\t" << strRd() << ", " << strRs() << ", " << strRt();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		TODO("Check for integer overflow");
		cpu.SGPR[u.r.rd] = cpu.SGPR[u.r.rs] + cpu.SGPR[u.r.rt];
	}
};

#endif
