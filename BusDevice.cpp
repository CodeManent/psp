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

/* Dumps the information contained in the request into the stream.
 */
std::ostream& operator<<(std::ostream &os, const BusDevice::Request &r)
{
	// lambda that returns the name of a device.
	static auto devName = [](const BusDevice::Device& d) noexcept {
		switch(d){
			case BusDevice::devCPU:	return "CPU";
			case BusDevice::devCPUCACHE: return "Cache";
			case BusDevice::devMainMemory: return "Main Memory";
			case BusDevice::devGraphicsCore: return "Graphics Core";
			case BusDevice::devAVCDecoder: return "AVC Decoder";
			case BusDevice::devDMAC: return "DMAC";
			case BusDevice::devVME: return "VME";
			case BusDevice::devMediaEngine: return "Media Engine";
			case BusDevice::devSubMemory: return "Sub Memory";
		}
		return "Unknown device";
	};

	os << std::setfill('0') << std::hex
		<< "Request{"
		<< "to: " << devName(r.to)
		<< ", from: " << devName(r.from)
		<< ", param1 = 0x" << std::setw(8) << r.param1
		<< ", param2 = 0x" << std::setw(8) << r.param2
		<< "}";
	return os;
}
