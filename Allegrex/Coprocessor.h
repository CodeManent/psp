#ifndef COPROCESSOR_H_
#define CORIOCESSOR_H_
#pragma once

#include "../IntTypes.h"

class Allegrex;

class Coprocessor
{
public:
	Coprocessor(Allegrex &a):cpu(a){};
	virtual ~Coprocessor(void){};

	uint32 reg[32];
	Allegrex &cpu;
};


#endif
