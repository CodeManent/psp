#include "PSP.h"

#include "MainMemory.h"
#include "Allegrex/Allegrex.h"

#include <stdexcept>

PSP::PSP(void):cpu(NULL), mainMemory(NULL)
{
	cpu = new Allegrex(this);
	mainMemory = new MainMemory(this);
}

PSP::~PSP(void)
{
	delete mainMemory;
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
	static_cast<Allegrex *>(cpu)->execute(0x3ff9983f);
//	while(true){
//	}
}

void PSP::sendRequest(const struct BusDevice::Request &r){
	requestQueue.push(r);
}

void PSP::forwardRequests(){

	while(!requestQueue.empty()){
		BusDevice::Request &req = requestQueue.front();

		switch(req.to){

	#define throwErrorCase(x) case BusDevice::x : throw(#x " is not connected")

		throwErrorCase(devCPU);

		case BusDevice::devMainMemory:
			mainMemory->serviceRequest(req);
			break;

		throwErrorCase(devGraphicsCore);
		throwErrorCase(devAVCDecoder);
		throwErrorCase(devDMAC);
		throwErrorCase(devVME);
		throwErrorCase(devMediaEngine);
		throwErrorCase(devSubMemory);

		default:
			throw std::logic_error("Device does not exist");
		}

		requestQueue.pop();
	}
}
