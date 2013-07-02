#ifndef PSP_H_
#define PSP_H_

#pragma once

//#include "Allegrex/Allegrex.h"
//#include "MainMemory.h"
//#include "GraphicsCore.h"
//#include "AVCDecoder.h"
//#include "DMAC.h"
//#include "VME.h"
//#include "MediaEngine.h"
//#include "SubMemory.h"

#include "BusDevice.h"

#include <cstddef> // size_t
#include <queue>

class PSP
{

	BusDevice *cpu;
	BusDevice *mainMemory;
	
	std::queue<BusDevice::Request> requestQueue;

public:
	PSP(void);
	~PSP(void);

	void run();
	void sendRequest(const struct BusDevice::Request &req);

private:
	void forwardRequests();

};

#endif
