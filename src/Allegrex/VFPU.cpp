#include "VFPU.h"

#include <cmath>
#include <cfenv> // handling of floationg point exceptions

//code assumes that floats are 32 bits
static_assert(sizeof(float) == sizeof(uint32),  "Float isn't 32 bits");
//and doubles are 64 bits
static_assert(sizeof(double) == 2*sizeof(uint32), "Bad double size");

struct {
	const char* name;
	float value;
} constants[] = {
	"ZERO",     0.0f,
	"HUGE",     HUGE_VALF, // Infinity
	"SQRT2",    sqrt(2.0),
	"SQRT1_2",  sqrt(1.0/2.0),
	"2/SQRTPI", 2.0/sqrt(M_PI),
	"2/PI",     2.0/M_PI,
	"1/PI",     1.0/M_PI,
	"PI/4",     M_PI/4.0,
	"PI/2",     M_PI/2.0,
	"PI",       M_PI,
	"E",        M_E,
	"LOG2E",    log2(M_E),
	"LOG10E",   log10(M_E),
	"LN2",      log(2.0),
	"LN10",     log(10),
	"2PI",      2.0 * M_PI,
	"PI/6",     M_PI / 6.0,
	"LOG10_2",  log10(2.0),
	"LOG2_10",  log2(10.0),
	"SQRT3/2",  sqrt(3.0) / 2.0,
};



VFPU::VFPU(Allegrex& cpu)
:Coprocessor(cpu)
{
	constants[0].value = constants[2].value;
}

VFPU::~VFPU(){
}


