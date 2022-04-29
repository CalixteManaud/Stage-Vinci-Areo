
#include <libusb/libusb.h>
#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	int error = libusb_init(NULL);

	if (error != 0)
	{
		std::cout << libusb_strerror(error) << std::endl;
		return EXIT_FAILURE;
	}

	libusb_device** devices = NULL;
	libusb_device* mcdu = NULL;
	int device_count = libusb_get_device_list(NULL, &devices);

	unsigned char string[255];

	if (device_count < 0)
		device_count = 0;

	std::cout << device_count << " devices found" << std::endl;

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

		std::cout << "Device" << std::endl;
		std::cout << "idVendorStr = " << hexVendor << std::endl;
		std::cout << "idProductStr = " << hexProduct << std::endl;

		if (hexVendor == "4d8" && hexProduct == "71")
		{
			std::cout << "mcdu detected" << std::endl;
			mcdu = devices[i];
			break;
		}
	}

	if (mcdu)
	{
		libusb_device_handle* device_handle = NULL;

		error = libusb_open(mcdu, &device_handle);

		if (error != 0)
			std::cout << "ERROR : " << libusb_strerror(error) << std::endl;

		if (device_handle)
		{
			std::cout << "Device opened" << std::endl;

			libusb_device_descriptor device_descriptor;
			error = libusb_get_device_descriptor(mcdu, &device_descriptor);


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

			for(unsigned int l = 0; l < 4; l++)
			{
				libusb_transfer* transfer = libusb_alloc_transfer(0);

				unsigned char data[512];
				int len = 0;
				if((error = libusb_interrupt_transfer(device_handle, 0x82, data, sizeof(data), &len, 0)) < 0)
				std::cout << "ERREUR " << libusb_strerror(error) << std::endl;
				//0x82 in
				//0x01 out

				/*for(unsigned int i = 0; i < len; i++)
					std::cout << (int)data[i] << ' ';
				std::cout << std::endl;*/

				unsigned int groupe = std::bitset<32>((data[1] & ~(1 << 6)) >> 1).to_ulong();

				unsigned int byte1 = ~(data[2]) & 255;
				byte1 = (byte1 & -byte1);
				if (byte1 != 0)
					byte1 = log2((byte1 & -byte1)) + 1;

				//std::cout << "Groupe " << groupe << std::endl;
				//std::cout << "Byte   " << byte1 << std::endl;

				std::string button = "Unknown";
				std::string state = "released";

				switch (groupe)
				{
				case 0:
					switch (byte1)
					{
					case 1:
						button = "Unknown";
						state = "pressed";
						break;
					case 2:
						button = "0";
						state = "pressed";
						break;
					case 3:
						button = "Plus";
						state = "pressed";
						break;
					case 4:
						button = "Z";
						state = "pressed";
						break;
					case 5:
						button = "Slash";
						state = "pressed";
						break;
					case 6:
						button = "SP";
						state = "pressed";
						break;
					case 7:
						button = "0VFY";
						state = "pressed";
						break;
					case 8:
						button = "CLR";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 1:
					switch (byte1)
					{
					case 1:
						button = "7";
						state = "pressed";
						break;
					case 2:
						button = "8";
						state = "pressed";
						break;
					case 3:
						button = "9";
						state = "pressed";
						break;
					case 4:
						button = "U";
						state = "pressed";
						break;
					case 5:
						button = "V";
						state = "pressed";
						break;
					case 6:
						button = "W";
						state = "pressed";
						break;
					case 7:
						button = "X";
						state = "pressed";
						break;
					case 8:
						button = "Y";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 2:
					switch (byte1)
					{
					case 1:
						button = "4";
						state = "pressed";
						break;
					case 2:
						button = "5";
						state = "pressed";
						break;
					case 3:
						button = "6";
						state = "pressed";
						break;
					case 4:
						button = "P";
						state = "pressed";
						break;
					case 5:
						button = "Q";
						state = "pressed";
						break;
					case 6:
						button = "R";
						state = "pressed";
						break;
					case 7:
						button = "S";
						state = "pressed";
						break;
					case 8:
						button = "T";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 3:
					switch (byte1)
					{
					case 1:
						button = "1";
						state = "pressed";
						break;
					case 2:
						button = "2";
						state = "pressed";
						break;
					case 3:
						button = "3";
						state = "pressed";
						break;
					case 4:
						button = "K";
						state = "pressed";
						break;
					case 5:
						button = "L";
						state = "pressed";
						break;
					case 6:
						button = "M";
						state = "pressed";
						break;
					case 7:
						button = "N";
						state = "pressed";
						break;
					case 8:
						button = "O";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 4:
					switch (byte1)
					{
					case 1:
						button = "Rarrow";
						state = "pressed";
						break;
					case 2:
						button = "Darrow";
						state = "pressed";
						break;
					case 3:
						button = "LSK6";
						state = "pressed";
						break;
					case 4:
						button = "F";
						state = "pressed";
						break;
					case 5:
						button = "G";
						state = "pressed";
						break;
					case 6:
						button = "H";
						state = "pressed";
						break;
					case 7:
						button = "I";
						state = "pressed";
						break;
					case 8:
						button = "J";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 5:
					switch (byte1)
					{
					case 1:
						button = "Larrow";
						state = "pressed";
						break;
					case 2:
						button = "Uarrow";
						state = "pressed";
						break;
					case 3:
						button = "LSK5";
						state = "pressed";
						break;
					case 4:
						button = "A";
						state = "pressed";
						break;
					case 5:
						button = "B";
						state = "pressed";
						break;
					case 6:
						button = "C";
						state = "pressed";
						break;
					case 7:
						button = "D";
						state = "pressed";
						break;
					case 8:
						button = "E";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 6:
					switch (byte1)
					{
					case 1:
						button = "AIRPORT";
						state = "pressed";
						break;
					case 2:
						button = "Unknown";
						state = "pressed";
						break;
					case 3:
						button = "LSK4";
						state = "pressed";
						break;
					case 4:
						button = "ATCCOMM";
						state = "pressed";
						break;
					case 5:
						button = "MCDUMENU";
						state = "pressed";
						break;
					case 6:
						button = "RSK2";
						state = "pressed";
						break;
					case 7:
						button = "RSK4";
						state = "pressed";
						break;
					case 8:
						button = "RSK6";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 7:
					switch (byte1)
					{
					case 1:
						button = "RADNAV";
						state = "pressed";
						break;
					case 2:
						button = "FPLN";
						state = "pressed";
						break;
					case 3:
						button = "LSK3";
						state = "pressed";
						break;
					case 4:
						button = "DATA";
						state = "pressed";
						break;
					case 5:
						button = "Unknown";
						state = "pressed";
						break;
					case 6:
						button = "RSK1";
						state = "pressed";
						break;
					case 7:
						button = "RSK3";
						state = "pressed";
						break;
					case 8:
						button = "RSK5";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				case 8:
					switch (byte1)
					{
					case 1:
						button = "PROG";
						state = "pressed";
						break;
					case 2:
						button = "DIR";
						state = "pressed";
						break;
					case 3:
						button = "LSK2";
						state = "pressed";
						break;
					case 4:
						button = "LSK1";
						state = "pressed";
						break;
					case 5:
						button = "SECFPLN";
						state = "pressed";
						break;
					case 6:
						button = "FUELPRED";
						state = "pressed";
						break;
					case 7:
						button = "PREF";
						state = "pressed";
						break;
					case 8:
						button = "INIT";
						state = "pressed";
						break;
					default:
						button = "Unknown";
						state = "released";
						break;
					}
					break;
				default:
					button = "Unknown";
					state = "released";
					break;
				}
				
				if(state != "released")
					std::cout << button << " button " << state << std::endl;
			}

			libusb_close(device_handle);
		}
	}

	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	std::cout << "Press any key to exit" << std::endl;
	std::cin.get();

	return EXIT_SUCCESS;
}

		
/*
	#code = MCDU_CPT.test([groupe, byte1])

	#print('Groupe : {}, Bit1 : {}, Code : {}'.format(groupe, byte1, code))
	except usb.core.USBError as e :
	data = None
	if e.args == ('Operation timed out', ) :
		continue
*/
