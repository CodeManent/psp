#include "MainMemory.h"
#include "IntTypes.h"

#include <stdexcept>

MainMemory::MainMemory(PSP *bus):BusDevice(bus)
{
}

MainMemory::~MainMemory(void)
{
}

uint32 MainMemory::read(const uint32 addr) const{
	return memory[addr>>2];
}

void MainMemory::write(const uint32 addr, const uint32 data){
	memory[addr>>2] = data;
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
