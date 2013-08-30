#include "MainMemory.h"
#include "IntTypes.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>

MainMemory::MainMemory(PSP *bus):BusDevice(bus)
{
}

MainMemory::~MainMemory(void)
{
}

/*
 * Returns the memory cell to be used for reading.
 * It checks the memory map and returns a reference to the memory cell
 * that will be used for reading. 
 */
const uint32& MainMemory::getCell(const uint32 addr) const{
	//find memory bank
	for(auto &entry: memoryMap)
		if(entry.start <= addr && addr <= entry.end)
			//and return a reference to the memory location
			return entry.data.at((addr - entry.start) >> 2);

	throw std::runtime_error("Main Memory: adress error");
}

/*
 * Returns the memory cell to be used for writting.
 * It is the same as for reading except it is not cosnt
 */
uint32& MainMemory::getCell(const uint32 addr){
	for(auto &entry: memoryMap)
		if(entry.start <= addr && addr <= entry.end)
			return entry.data.at((addr - entry.start) >> 2);
	
	throw std::runtime_error("Main Memory: Address error");
}


uint32 MainMemory::read(const uint32 addr) const{
//	std::cout << "Reading from 0x"
//		<< std::setw(8) << std::setfill('0') << std::hex << addr << std::endl;
	return getCell(addr);
}

void MainMemory::write(const uint32 addr, const uint32 data){
	getCell(addr) = data;
}

void MainMemory::serviceRequest(const struct BusDevice::Request &req){
	if((req.param1 & 0x00000003) != 0){
		throw std::logic_error("MainMemory: bus error");
	}

	switch(req.function){
		case BusDevice::Read://read param1
			{
				BusDevice::Request r = {
					devMainMemory,
					req.from,
					BusDevice::Reply,
					read(req.param1),
					0//unused
				};
				sendRequest(r);
			}
			break;

		case BusDevice::Write://write param2 at param1
			write(req.param1, req.param2);
			break;

		default:
			throw std::logic_error("MainMemory: bad request to service");
	}
}
