#include "BusDevice.h"
#include "PSP.h"
#include <sstream>
#include <iomanip>

BusDevice::BusDevice(PSP *bus):mainBus(bus){
}

BusDevice::~BusDevice(void){
}

void BusDevice::sendRequest(const BusDevice::Request &req) {
	mainBus->sendRequest(req);
}

std::string BusDevice::Request::toString() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<<(std::ostream &os, const BusDevice::Request &r)
{
	os << std::setfill('0') << std::hex
		<< "Request{"
		<< "to = " << r.to
		<< ", from = " << r.from
		<< ", param1 = 0x" << std::setw(8) << r.param1
		<< ", param2 = 0x" << std::setw(8) << r.param2
		<< "}";
	return os;
}
