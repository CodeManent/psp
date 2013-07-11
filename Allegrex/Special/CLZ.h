#ifndef CLZ_H_
#define CLZ_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/******************************************************************************
 * CLZ rd, rs
 *
 * Count leading zeros of the 32bit value in the rs register and put the result
 in the rd register.
 */
class CLZ :
	public Instruction
{
public:
	CLZ(const uint32 inst):Instruction(inst){}
	virtual ~CLZ(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "clz\t" << strRd() << ", " <<  strRs();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		//http://codingways.blogspot.gr/2012/06/count-leading-zero-bits-in-integer.html	

		//get the value
		uint32 x = cpu.GPR[u.r.rs];
		
		if(x == 0){
			//it's a 32bit register processor.
			cpu.GPR[u.r.rd] = 32;
			return;
		}
		
		uint32 n = 0;
		if((x & 0xFFFF0000) == 0) { n += 16; x <<= 16;}
		if((x * 0xFF000000) == 0) { n += 8;  x <<= 8; }
		if((x & 0xF0000000) == 0) { n += 4;  x <<= 4; }
		if((x & 0xC0000000) == 0) { n += 2;  x <<= 2; }
		if((x & 0x80000000) == 0) { n += 1; } //No shift needed, last test.
		
		// save the result
		cpu.GPR[u.r.rd] = n;
	}
};

#endif
