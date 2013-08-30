#ifndef MAIN_MEMORY_H_
#define MAIN_MEMORY_H_
#pragma once

#include "BusDevice.h"
#include "IntTypes.h"
#include <vector>

class MainMemory:
	public BusDevice
{
	struct MapEntry{
		uint32 start;				// Starting adress
		uint32 end;					// ending address
		std::vector<uint32> data;	// Size of the 
		const char* description;	// Text about the memory map entry
	};
	
	// mapping oh=f the physical memory
	MapEntry memoryMap[3] = {
		// start   , end       , vector(size) , description
		{0x00000000, 0x001fffff, std::vector<uint32>(0x00200000 >> 2), "ME internal memory"},
		{0x08000000, 0x09ffffff, std::vector<uint32>(0x02000000 >> 2), "Main Memory"},
		{0x1fc00000, 0x1fcfffff, std::vector<uint32>(0x00100000 >> 2), "Hardware exception vectors"}
	};

	//MapEntry ramUsage[3];

//Public for testing purposes	
public:
	const uint32& getCell(const uint32 addr) const;
	uint32& getCell(const uint32 addr);
	uint32 read(const uint32 addr) const;
	void write(const uint32 addr, const uint32 data);
public:
	MainMemory(PSP *bus);
	~MainMemory(void);

	void serviceRequest(const BusDevice::Request &req);
};

#endif
