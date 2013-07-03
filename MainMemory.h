#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_
#pragma once

#include "BusDevice.h"
#include "IntTypes.h"

class MainMemory:
	public BusDevice
{
	uint32 memory[8*1024*1024]; //32MB

//Public for testing purposes	
public:
	uint32 read(const uint32 addr) const;
	void write(const uint32 addr, const uint32 data);
public:
	MainMemory(PSP *bus);
	~MainMemory(void);

	void serviceRequest(const BusDevice::Request &req);
};

#endif
