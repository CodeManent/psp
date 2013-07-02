#include "BusDevice.h"
#include "PSP.h"

BusDevice::BusDevice(PSP *bus):mainBus(bus){
}

BusDevice::~BusDevice(void){
}

void BusDevice::sendRequest(const BusDevice::Request &req) {
	mainBus->sendRequest(req);
}

