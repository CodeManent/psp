#ifndef CLO_H_
#define CLO_H_
#pragma once

#include "../Instruction.h"
#include <sstream>

/******************************************************************************
 * CLO rd, rs
 *
 * Count leading ones of the 32bit value in the rs register and put the result
 in the rd register.
 */
class CLO :
	public Instruction
{
public:
	CLO(const uint32 inst):Instruction(inst){}
	virtual ~CLO(void){}

	virtual std::string disassemble() const{
		std::stringstream ss;

		ss << "clo\t" << strRd() << ", " <<  strRs();

		return ss.str();
	}
	
	virtual void execute(Allegrex &cpu) const{
		//http://codingways.blogspot.gr/2012/06/count-leading-zero-bits-in-integer.html

		//We use the coun leading zeros algorithm but first we negate the source.

		//get the value
		uint32 x = ~(cpu.GPR[u.r.rs]);
		
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
