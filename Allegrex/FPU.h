#ifndef ALLEGREX_FPU_H
#define ALLEGREX_FPU_H

#include "Coprocessor.h"

class FPU: public Coprocessor{
	public:
	FPU(Allegrex& cpu);
	virtual ~FPU();

	private:
	// floating point control registers
	uint32 FCR[32];

	// Only two of the control registers are used. FCR1..FCR31 are reserved.
	// FCR0 coprocessor implementation and revision register
	struct FCR0{
		unsigned int Rev: 8; // Revision number in form x.y
		                     // y: major revision number held in bits 7:4
							 // x: minor revision number held in bits 3:0
		unsigned int Imp: 8; // Implementation number (0x05)
		unsigned int Reserved: 16;
	} &revision;
	// FCR31 Rounding mode, cause, trap enables and flags.
	struct FCR31{
		unsigned int RM: 2; // rounding mode
		unsigned int Flags: 5;
		unsigned int Enables: 5;
		unsigned int Cause: 6;
		unsigned int recerved: 5;
		unsigned int C: 1; // condition bit
		unsigned int FS:1; // when set, denormalized results are flushed to 0
		                   // instead of causing an unimplemented operation
						   // exception
		unsigned int reserved1: 7;
	} status;

	/*
	links to use for handling floating point exceptions
	http://stackoverflow.com/questions/16804519/handling-floating-point-exceptions-in-c
	http://en.cppreference.com/w/cpp/numeric/fenv/fetestexcept
	*/
		
	
	// FR bit of status reg decides which one is used
	// 
	float (&FGR)[32];
	double (&FPR)[16];
};


#endif

