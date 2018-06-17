#ifndef PSP_H_
#define PSP_H_

#pragma once

//#include "Allegrex/Allegrex.h"
#include "MainMemory.h"
//#include "GraphicsCore.h"
//#include "AVCDecoder.h"
//#include "DMAC.h"
//#include "VME.h"
//#include "MediaEngine.h"
//#include "SubMemory.h"

#include "BusDevice.h"

#include <cstddef> // size_t
#include <queue>
#include <memory>

class MainMemory;
class Allegrex;

class PSP
{

	std::unique_ptr<BusDevice> cpu;
	
	std::queue<BusDevice::Request> requestQueue;
	struct memoryMapEntry{
		uint32 start;
		uint32 end;
		std::unique_ptr<BusDevice> device;
		const char *description;
	};
	std::vector<memoryMapEntry> memoryMap;

public:
	PSP(void);
	~PSP(void);

	void run();
	void sendRequest(const struct BusDevice::Request &req);

	//Testing methods (to be removed)
	Allegrex* getCPU();

	MainMemory* getMainMemory();

private:
	void forwardRequests();

};

#endif
