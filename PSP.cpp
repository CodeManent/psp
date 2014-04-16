#include "PSP.h"

#include "MainMemory.h"
#include "Allegrex/Allegrex.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

PSP::PSP(void)
{
	struct entryDescriptor{
		uint32 start;
		uint32 end;
		const char* description;
		const char *path;
	} edl[] = {
		// TODO: remove line or add it as ME memory.
		{0x00000000, 0x000fffff, "Added because errors", "../Data/msipl.bin"},
		{0x00010000, 0x00013fff, "Scratchpad", ""},
		{0x04000000, 0x041fffff, "Video Memory/Frame buffer", ""},
		{0x08000000, 0x09ffffff, "Main Memory", ""},
		//{0x1c000000, 0x1fbfffff, "Hardware I/O" ""},
		{0x1fc00000, 0x1fcfffff, "Hardware Exception Vectors (RAM)", "../Data/msipl.bin"},
		{0x1fd00000, 0x1fdfffff, "Testan IPL", "../Data/msipl.bin"}
		//{0x1fd00000, 0x1fffffff, "Hardware I/O", ""}
	};

	for(auto &e : edl){
		std::unique_ptr<BusDevice> bd(
			new MainMemory(this, e.start, e.end-e.start+1, e.path)
		);

		memoryMapEntry mme = {
			e.start,
			e.end,
			std::move(bd),
			e.description
		};
		memoryMap.emplace_back(std::move(mme));
	}

	cpu.reset(new Allegrex(this));
}

PSP::~PSP(void)
{
}

void PSP::run(){
//	send initial signals
//		reset cpu
//		load initial main memory
//	while(true)
//		step devices
//		push messages
	const BusDevice::Request r = {
		BusDevice::devCPU,
		BusDevice::devCPU,
		BusDevice::Reset,
		0,
		0
	};
	cpu->serviceRequest(r);

	while(true){
		dynamic_cast<Allegrex *>(cpu.get())->step();
		forwardRequests();
	}
}

/*
 * The method that is called to send a request from a device to another
 *
 * HACK: immediately forward the request to the interested device
 */
void PSP::sendRequest(const struct BusDevice::Request &r){
	requestQueue.push(r);

	forwardRequests();
}

/*
 * Forwards the requests between devices.
 *
 * Right now it is used only for communication between the cpu and the 
 * main memory (and in a hackins way of them handling the requests).
 */
void PSP::forwardRequests(){

	while(!requestQueue.empty()){
		BusDevice::Request &req = requestQueue.front();
		requestQueue.pop();

		switch(req.to){

	#define throwErrorCase(x) case BusDevice::x : throw(#x " is not connected")

		// Messages (data) going to the CPU's cache are routed through the CPU.
		case BusDevice::devCPUCACHE:
		case BusDevice::devCPU:
			cpu->serviceRequest(req);
			break;

		case BusDevice::devMainMemory:
			// Select memory map entry by examining the address (re1.param1)
			for(auto &e : memoryMap){
			/*
				std::cerr << std::hex
					<< "PSP: Memory: Checking "
					<< e.start << " <= " << req.param1
					<< " (=" << (e.start <= req.param1) << ") && "
					<< req.param1 << " <= " << e.end
					<< "i (=" << (req.param1 <= e.end) << ") --> "
					<< ((e.start <= req.param1) && (req.param1 <= e.end))
					<< std::endl;
				*/
				if((e.start <= req.param1) && (req.param1 <= e.end)){
					e.device->serviceRequest(req);
					return;
				}
			}

			throw std::runtime_error(
				std::string("PSP: Address not in an allocated memory space: ")
				+ req.toString());
			break;

		throwErrorCase(devGraphicsCore);
		throwErrorCase(devAVCDecoder);
		throwErrorCase(devDMAC);
		throwErrorCase(devVME);
		throwErrorCase(devMediaEngine);
		throwErrorCase(devSubMemory);

		default:
			throw std::logic_error("PSP:Device does not exist: " + req.toString());
		}
	}
}

Allegrex* PSP::getCPU(){
	return dynamic_cast<Allegrex*>(cpu.get());
}

MainMemory* PSP::getMainMemory(){
	for(auto &me : memoryMap){
		if(std::string(me.description) == "Main Memory"){
			return dynamic_cast<MainMemory*>(me.device.get());
		}
	}

	throw std::runtime_error("PSP: Couldn't find Main memory");
}
