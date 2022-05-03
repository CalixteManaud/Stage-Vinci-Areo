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
	
	/*if (device)
	{
		unsigned char string[255];

		libusb_device_handle* device_handle = NULL;

		int error = libusb_open(device, &device_handle);

		if (error < 0)
			std::cout << libusb_strerror(error) << std::endl;

		if (device_handle)
		{
			std::cout << "Device opened" << std::endl;

			libusb_device_descriptor device_descriptor;
			error = libusb_get_device_descriptor(device, &device_descriptor);


			if (device_descriptor.iManufacturer) {
				error = libusb_get_string_descriptor_ascii(device_handle, device_descriptor.iManufacturer, string, sizeof(string));
				if (error > 0)
					printf("  Manufacturer:              %s\n", (char*)string);
			}

			if (device_descriptor.iProduct) {
				error = libusb_get_string_descriptor_ascii(device_handle, device_descriptor.iProduct, string, sizeof(string));
				if (error > 0)
					printf("  Product:                   %s\n", (char*)string);
			}

			if (device_descriptor.iSerialNumber) {
				error = libusb_get_string_descriptor_ascii(device_handle, device_descriptor.iSerialNumber, string, sizeof(string));
				if (error > 0)
					printf("  Serial Number:             %s\n", (char*)string);
			}

			unsigned char data2[512];
			int length = 0;

			std::cout << "Clearing queue..." << std::endl;
			do
			{
				if((error = libusb_interrupt_transfer(device_handle, 0x82, data2, sizeof(data2), &length, 1000)) < 0)
					std::cout << "CAMARCHEPAS" << std::endl;
			} while(length > 0);
			std::cout << "Done" << std::endl;

			for(unsigned int l = 0; l < 4; l++)
			{
				unsigned char data[512];
				int len = 0;
				if((error = libusb_interrupt_transfer(device_handle, 0x82, data, sizeof(data), &len, 0)) < 0)
					std::cout << libusb_strerror(error) << std::endl;
				//0x82 in
				//0x01 out
				std::cout << "Data recieved : " << std::endl;
				for(unsigned int i = 0; i < len; i++)
					std::cout << (int)data[i] << ' ';
				std::cout << std::endl;
			}
		}
	}

	return;*/

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
		error = libusb_interrupt_transfer(deviceHandle, 0x82, data, sizeof(data), &length, 1000);

		if(error < 0)
			std::cout << libusb_strerror(error) << std::endl;
	} while (length > 0);
	std::cout << "Done" << std::endl;

	//for(unsigned int l = 0; l < 4; l++)
	while(device)
			{
				//std::cout << "here : " << l << std::endl;
				std::cout << "here" << std::endl;
				unsigned char data2[512];
				int len = 0;
				if((error = libusb_interrupt_transfer(deviceHandle, 0x82, data2, sizeof(data2), &len, 0)) < 0)
					std::cout << libusb_strerror(error) << std::endl;
				//0x82 in
				//0x01 out
				//std::cout << "Data recieved : " << std::endl;
				for(unsigned int i = 0; i < len; i++)
				{
					std::cout << "printing stuff" << std::endl;
					std::cout << (int)data2[i] << ' ';
				}
				//std::cout << std::endl;
			}

	/*while (device)
	{
		//continue;

		if ((error = libusb_interrupt_transfer(deviceHandle, 0x82, data, sizeof(data), &length, 0)) < 0)
			std::cout << libusb_strerror(error) << std::endl;

		//0x82 in
		//0x01 out

		std::cout << "Data recieved : " << std::endl;
		for(unsigned int i = 0; i < length; i++)
			std::cout << (int)data[i] << ' ';
		std::cout << std::endl;

		*group = std::bitset<32>((data[1] & ~(1 << 6)) >> 1).to_ulong();

		int tbyte = ~(data[2]) & 255;
		tbyte = (tbyte & -tbyte);
		if (tbyte != 0)
			tbyte = (int)log2((tbyte & -tbyte)) + 1;

		*byte = tbyte;

		*byte = ~(data[2]) & 255;
		*byte = (*byte & -(*byte));
		if (*byte != 0)
			*byte = log2((*byte & -(*byte))) + 1;

		*dataRecieved = true;
	}*/
}
