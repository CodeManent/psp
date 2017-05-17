#ifndef ALLEGREX_VFPU_H
#define ALLEGREX_VFPU_H

#include "Coprocessor.h"

class VFPU: public Coprocessor{
	public:
	VFPU(Allegrex& cpu);
	virtual ~VFPU();
};


#endif

