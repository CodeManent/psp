#ifndef COPROCESSOR_H_
#define CORIOCESSOR_H_
#pragma once

#include "../IntTypes.h"
#include <stdexcept>

class Allegrex;

class Coprocessor
{
public:
	Coprocessor(Allegrex &a):cpu(a){};
	virtual ~Coprocessor(void){};

	virtual void setReg(unsigned int regNo, uint32 value){
		if(!(regNo < 32))
			throw std::range_error("Register number out of range");

		reg[regNo] = value;
	}

	virtual uint32 getReg(unsigned int regNo){
		if(!(regNo < 32))
			throw std::range_error("Register number out of range");
		
		return reg[regNo];
	}

	uint32 reg[32];
	Allegrex &cpu;
};


#endif
