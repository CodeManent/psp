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

	//static_cast<Allegrex *>(cpu)->execute(0x3ff9983f);
	while(true){
		static_cast<Allegrex *>(cpu)->step();
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

		//throwErrorCase(devCPU);

		case BusDevice::devCPU:
			cpu->serviceRequest(req);
			break;

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
	}
}

Allegrex* PSP::getCPU(){
	return dynamic_cast<Allegrex*>(cpu);
}

MainMemory* PSP::getMainMemory(){
	return dynamic_cast<MainMemory*>(mainMemory);
}

