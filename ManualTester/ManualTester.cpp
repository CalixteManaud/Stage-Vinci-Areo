
#include <libusb/libusb.h>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        std::cout << "Too few arguments provided" << std::endl;
        std::cout << "Please use the following syntax : sudo ./ManualTester.run [idVendor] [idProduct] [nbInput]" << std::endl;
        return 0;
    }

    std::string idVendor = argv[1];
    std::string idProduct = argv[2];
    unsigned int nbInput = std::stoul(argv[3]);

	int error = libusb_init(NULL);

	if (error != 0)
	{
		std::cout << libusb_strerror(error) << std::endl;
		return EXIT_FAILURE;
	}

	libusb_device** devices = NULL;
	libusb_device* device = NULL;
	int device_count = libusb_get_device_list(NULL, &devices);

	unsigned char string[255];

	if (device_count < 0)
		device_count = 0;

	for (unsigned int i = 0; i < (unsigned int)device_count; i++)
	{
		libusb_device_descriptor device_descriptor;
		error = libusb_get_device_descriptor(devices[i], &device_descriptor);

		if (error != 0)
		{
			std::cout << libusb_strerror(error) << std::endl;
			return EXIT_FAILURE;
		}

		std::ostringstream osstr;
		osstr << std::hex << device_descriptor.idVendor;
		std::string hexVendor = osstr.str();
		osstr.str("");
		osstr << std::hex << device_descriptor.idProduct;
		std::string hexProduct = osstr.str();

		if (hexVendor == idVendor && hexProduct == idProduct)
		{
			std::cout << "Device found" << std::endl;
			device = devices[i];
			break;
		}
	}

	if (!device)
    {
        std::cout << "Device not found" << std::endl;
        return 0;
    }

    libusb_device_handle* device_handle = NULL;

    error = libusb_open(device, &device_handle);

    if (error != 0)
        std::cout << libusb_strerror(error) << std::endl;

    if (!device_handle)
    {
        std::cout << "Failed to open device" << std::endl;
        return 0;
    }

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
        libusb_interrupt_transfer(device_handle, 0x82, data2, sizeof(data2), &length, 1000);
    } while(length > 0);
    std::cout << "Done" << std::endl;

    for(unsigned int l = 0; l < nbInput; l++)
    {
        unsigned char data[512];
        int len = 0;
        if((error = libusb_interrupt_transfer(device_handle, 0x82, data, sizeof(data), &len, 0)) < 0)
            std::cout << libusb_strerror(error) << std::endl;

        for(unsigned int i = 0; i < len; i++)
            std::cout << (int)data[i] << ' ';
        std::cout << std::endl;
    }

    libusb_close(device_handle);

	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	std::cout << "Press enter to exit" << std::endl;
	std::cin.get();

	return EXIT_SUCCESS;
}
