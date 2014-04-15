#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_
#pragma once

#include "BusDevice.h"
#include "IntTypes.h"
#include <vector>
#include <string>

class MainMemory:
	public BusDevice
{
	uint32 base;
	std::vector<uint32> memory;

//Public for testing purposes	
public:
	const uint32& getCell(const uint32 addr) const;
	uint32& getCell(const uint32 addr);
	uint32 read(const uint32 addr) const;
	void write(const uint32 addr, const uint32 data);
public:
	MainMemory(PSP *bus, uint32 base, uint32 size, const std::string path = "");
	~MainMemory(void);

	void serviceRequest(const BusDevice::Request &req);
};

#endif
