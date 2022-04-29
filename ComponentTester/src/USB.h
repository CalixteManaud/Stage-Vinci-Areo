#pragma once

#include <libusb/libusb.h>

#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class USB
{
private:
	libusb_device** m_devices;
	unsigned int m_deviceCount;

public:
	USB();
	~USB();

	libusb_device* getDevice(const std::string& idVendor, const std::string& idProduct);
	void readDevice(libusb_device* device, unsigned int* group, unsigned int* byte, bool* dataRecieved);
};