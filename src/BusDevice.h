#ifndef BUS_DEVICE_H_
#define BUS_DEVICE_H_
#pragma once

#include "IntTypes.h"

#include <cstddef> //size_t
#include <iostream>

class PSP;

class BusDevice
{
	PSP *mainBus;
public:
	enum Device{
		devCPU,
		devCPUCACHE,
		devMainMemory,
		devGraphicsCore,
		devAVCDecoder,
		devDMAC,
		devVME,
		devMediaEngine,
		devSubMemory
	};

	enum Function{
		Read,
		Write,
		Reply,
		Reset
	};


	struct Request{
		enum Device from;
		enum Device to;
		enum Function function;
		uint32 param1;
		uint32 param2;
		std::string toString() const;
	};

	BusDevice(PSP *bus);
	virtual ~BusDevice(void);

	virtual void serviceRequest(const struct Request &req) = 0;

protected:
	virtual void sendRequest(const struct Request &req);
};

std::ostream& operator<<(std::ostream &os, const BusDevice::Request &r);

#endif
