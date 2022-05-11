#include "USB.h"

USB::USB(bool debugInfo) :
	m_devices(NULL),
	m_deviceCount(0),
	m_deviceHandle(NULL),
	m_debugInfo(debugInfo)
{
	if(m_debugInfo)
		std::cout << "Detecting devices..." << std::endl;

	int error = libusb_init(NULL);

	if (m_debugInfo && error != 0)
		std::cout << libusb_strerror(error) << std::endl;

	int deviceCount = libusb_get_device_list(NULL, &m_devices);

	if (deviceCount < 0)
		deviceCount = 0;

	m_deviceCount = (unsigned int)deviceCount;

	if(m_debugInfo)
	{
		std::cout << m_deviceCount << (m_deviceCount > 1 ? " devices" : " device") << " detected" << std::endl;

		for (unsigned int i = 0; i < (unsigned int)m_deviceCount; i++)
		{
			libusb_device_descriptor device_descriptor;
			error = libusb_get_device_descriptor(m_devices[i], &device_descriptor);

			if (error != 0)
				std::cout << libusb_strerror(error) << std::endl;

			std::ostringstream osstr;
			osstr << std::hex << device_descriptor.idVendor;
			std::string hexVendor = osstr.str();
			osstr.str("");
			osstr << std::hex << device_descriptor.idProduct;
			std::string hexProduct = osstr.str();

			std::cout << "Device " << i+1 << ": " << hexVendor << ":" << hexProduct << std::endl;
		}
	}
}
USB::~USB()
{
	if(m_deviceHandle)
		libusb_close(m_deviceHandle);
		
	libusb_free_device_list(m_devices, 1);
	libusb_exit(NULL);
}

void USB::close()
{
	libusb_close(m_deviceHandle);
	m_deviceHandle = NULL;
}

libusb_device* USB::getDevice(const std::string& idVendor, const std::string& idProduct)
{
	libusb_device* device = NULL;
	int error = 0;

	for (unsigned int i = 0; i < m_deviceCount; i++)
	{
		libusb_device_descriptor device_descriptor;
		error = libusb_get_device_descriptor(m_devices[i], &device_descriptor);

		if (m_debugInfo && error != 0)
			std::cout << libusb_strerror(error) << std::endl;

		std::ostringstream osstr;
		osstr << std::hex << device_descriptor.idVendor;
		std::string hexVendor = osstr.str();
		osstr.str("");
		osstr << std::hex << device_descriptor.idProduct;
		std::string hexProduct = osstr.str();

		if (hexVendor == idVendor && hexProduct == idProduct)
		{
			device = m_devices[i];
			break;
		}
	}

	return device;
}
void USB::readDevice(libusb_device* device, bool* reading, bool* dataRecieved, unsigned char* data)
{
	if (!device)
	{
		if(m_debugInfo)
			std::cout << "No device provided for this component" << std::endl;
		return;
	}

	m_deviceHandle = NULL;
	int error = libusb_open(device, &m_deviceHandle);

	if (m_debugInfo && error < 0)
		std::cout << libusb_strerror(error) << std::endl;

	if (m_debugInfo && !m_deviceHandle)
	{
		std::cout << "Failed to open device" << std::endl;
		return;
	}

	libusb_device_descriptor device_descriptor;
	error = libusb_get_device_descriptor(device, &device_descriptor);
	
	int length = 0;

	if(m_debugInfo)
		std::cout << "Clearing queue..." << std::endl;
	do
	{
		error = libusb_interrupt_transfer(m_deviceHandle, 0x82, data, sizeof(data), &length, 1000);

		//if(m_debugInfo && error < 0)
		//	std::cout << libusb_strerror(error) << std::endl;
			
	} while (length > 0);
	if(m_debugInfo)
		std::cout << "Done" << std::endl;

	while(*reading)
	{
		while(*dataRecieved);

		error = libusb_interrupt_transfer(m_deviceHandle, 0x82, data, sizeof(data), &length, 0);

		if(m_debugInfo && error < 0 && error != LIBUSB_ERROR_NO_DEVICE)
			std::cout << libusb_strerror(error) << std::endl;

		*dataRecieved = true;
	}
}
