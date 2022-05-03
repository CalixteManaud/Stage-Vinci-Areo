#include "USB.h"

USB::USB() :
	m_devices(NULL),
	m_deviceCount(0)
{
	int error = libusb_init(NULL);

	if (error != 0)
		std::cout << libusb_strerror(error) << std::endl;

	int deviceCount = libusb_get_device_list(NULL, &m_devices);

	if (deviceCount < 0)
		deviceCount = 0;

	m_deviceCount = (unsigned int)deviceCount;

	std::cout << m_deviceCount << " devices found" << std::endl;

	/*for (unsigned int i = 0; i < (unsigned int)m_deviceCount; i++)
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

		std::cout << "Device" << std::endl;
		std::cout << "idVendorStr = " << hexVendor << std::endl;
		std::cout << "idProductStr = " << hexProduct << std::endl;
	}*/
}
USB::~USB()
{
	libusb_free_device_list(m_devices, 1);
	libusb_exit(NULL);
}

libusb_device* USB::getDevice(const std::string& idVendor, const std::string& idProduct)
{
	libusb_device* device = NULL;
	int error = 0;

	for (unsigned int i = 0; i < m_deviceCount; i++)
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

		//if (hexVendor == "4d8" && hexProduct == "71")
		if (hexVendor == idVendor && hexProduct == idProduct)
		{
			device = m_devices[i];
			break;
		}
	}

	return device;
}
void USB::readDevice(libusb_device* device, unsigned int* group, unsigned int* byte, bool* dataRecieved)
{
	if (!device)
	{
		std::cout << "No device provided" << std::endl;
		return;
	}

	libusb_device_handle* deviceHandle = NULL;
	int error = libusb_open(device, &deviceHandle);

	if (error < 0)
		std::cout << libusb_strerror(error) << std::endl;

	if (!deviceHandle)
	{
		std::cout << "Failed to open device" << std::endl;
		return;
	}

	libusb_device_descriptor device_descriptor;
	error = libusb_get_device_descriptor(device, &device_descriptor);
	
	unsigned char data[512];
	int length = 0;

	std::cout << "Clearing queue..." << std::endl;
	do
	{
		if((error = libusb_interrupt_transfer(deviceHandle, 0x82, data, sizeof(data), &length, 1000)) < 0)
			std::cout << libusb_strerror(error) << std::endl;
			
	} while (length > 0);
	std::cout << "Done" << std::endl;

	while(device)
	{
		unsigned char data2[512];
		int len = 0;

		while(*dataRecieved);

		if((error = libusb_interrupt_transfer(deviceHandle, 0x82, data2, sizeof(data2), &len, 0)) < 0)
			std::cout << libusb_strerror(error) << std::endl;

		/*for(unsigned int i = 0; i < len; i++)
			std::cout << (int)data2[i] << ' ';
		std::cout << std::endl;*/

		unsigned int groupe = std::bitset<32>((data2[1] & ~(1 << 6)) >> 1).to_ulong();

		unsigned int byte1 = ~(data2[2]) & 255;
		byte1 = (byte1 & -byte1);
		if (byte1 != 0)
			byte1 = log2((byte1 & -byte1)) + 1;

		*group = groupe;
		*byte = byte1;

		*dataRecieved = true;
	}
}
