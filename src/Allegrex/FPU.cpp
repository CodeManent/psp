#include "FPU.h"
#include <cfenv> // handling of floationg point exceptions
FPU::FPU(Allegrex& cpu)
:Coprocessor(cpu)
,revision(reinterpret_cast<FCR0&>(FCR[0]))
,status(reinterpret_cast<FCR31&>(FCR[31]))
,FGR(reinterpret_cast<float(&)[32]>(reg))
,FPR(reinterpret_cast<double(&)[16]>(reg))
{
	//code assumes that floats are 32 bits
	static_assert(sizeof(float) == sizeof(uint32),  "Float isn't 32 bits");
	//and doubles are 64 bits
	static_assert(sizeof(double) == 2*sizeof(uint32), "Bad double size");

	static_assert(sizeof(FCR0) == sizeof(uint32),
		"Struct FCR0 equals floating point control register size");
	static_assert(sizeof(FCR31) == sizeof(uint32),
		"Struct FCR31 equals floating point control register size");


}

FPU::~FPU(){
}


