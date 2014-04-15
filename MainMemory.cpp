#include "MainMemory.h"
#include "IntTypes.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "Allegrex/Instruction.h"

MainMemory::MainMemory(PSP *bus, uint32 base, uint32 size, const std::string path)
:BusDevice(bus),
base(base)
{
	//allocate the memory
	memory.resize(size >> 2);
	
	//load the file into memory, if one specified
	if(path.length() != 0){
	try{
		//open file and read it
		std::ifstream f(path);
		f.exceptions(std::ios_base::badbit | std::ios_base::failbit);
		std::vector<char> charFile;
		std::copy(
			std::istreambuf_iterator<char>(f),
			std::istreambuf_iterator<char>(),
			std::back_inserter(charFile)
		);

		// get the top so as to not go over the size of the memory vector if
		// the file is bigger
		auto top = charFile.size() /sizeof(uint32);
		top = std::min(top, memory.size());

		// copy the data in the memory vector as ints.
		for(size_t i = 0; i < top; ++i){
			uint32 val = 0;
			for(size_t p = 0; p < sizeof(uint32); ++p){
				// unsigned char to avoid sign expansion
				uint32 tmp = (unsigned char) charFile[sizeof(uint32)*i + p];
				tmp <<= p*8;
				val |= tmp;
			}
			memory[i] = val;
		}
	}
	catch(const std::exception &e){
		std::string msg = "Couldn't load file: " + path;
		std::throw_with_nested( std::runtime_error(msg));
	}
	}
}


MainMemory::~MainMemory(void)
{
}

uint32 MainMemory::read(const uint32 addr) const{
	return memory.at((addr-base) >> 2);
}

void MainMemory::write(const uint32 addr, const uint32 data){
	memory.at((addr-base) >> 2) = data;
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
