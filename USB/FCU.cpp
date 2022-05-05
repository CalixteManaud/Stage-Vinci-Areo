#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

#include <unistd.h>

#include <libusb/libusb.h>

std::vector<std::vector<unsigned int>> outs;

std::vector<std::vector<unsigned int>> outputs;
std::vector<std::vector<unsigned int>> outputs2;

std::vector<unsigned int> codeOUT(13);


std::vector<std::vector<unsigned int>> outputsOfCode(unsigned int code)
{
	
	if (std::find(codeOUT.begin(), codeOUT.end(), code) != codeOUT.end())
	{
		std::vector<std::vector<unsigned int>> r;
		std::vector<unsigned int> o;
		std::vector<unsigned int>::iterator index = std::find(codeOUT.begin(), codeOUT.end(), code);

		if (index != codeOUT.end())
			o = outputs[index - codeOUT.begin()];
			//o = *index;
			//o = codeOUT[index - codeOUT.begin()];

		for (unsigned int i = 0; i < o.size(); i++)
			r.push_back(outputs2[i + o[1]]);

		return r;
	}
	return std::vector<std::vector<unsigned int>>(0);
}

void output_sequence(bool on, bool all, libusb_device_handle* device_handle)
{
	if (all)
	{
		unsigned int code = 300;
		std::vector<unsigned int> invalid_codes = { 313, 315, 316, 317, 318, 319, 320, 321, 339 };

		for (unsigned int i = 0; i < 39; ++i)
		{
			std::cout << "code = " << code << std::endl;

			if (std::find(invalid_codes.begin(), invalid_codes.end(), code) != invalid_codes.end())
			{
				std::cout << "Invalid code" << std::endl;
				code++;
				continue;
			}

			std::vector<std::vector<unsigned int>> out = outputsOfCode(code);
			code++;

			unsigned int byte;

			for (unsigned j = 0; j < out.size(); j++)
			{
				byte = std::pow(out[j][2], 2);

				if (on)
				{
					if (out[j][1] == 0)
					{
						outs[out[j][0]][2] |= byte;

						//unsigned int val = std::stoul(outs[out[j][0]][2]);
						//val |= byte;
					}	
					else
						outs[out[j][0]][3] |= byte;
				}
				else
				{
					byte = ~byte;

					if (out[j][1] == 0)
						outs[out[j][0]][2] &= byte;
					else
						outs[out[j][0]][3] &= byte;
				}
			
				// -----

				libusb_transfer* transfer = libusb_alloc_transfer(0);

				int error = 0;
				//unsigned char* data = outs[out[j][0]];

				std::string dat;
				for(unsigned int k = 0; k < outs[out[j][0]].size(); k++)
					dat.insert(dat.end(), outs[out[j][0]].begin(), outs[out[j][0]].end());
				unsigned char* data = (unsigned char*)(dat.c_str());
				int len = 0;
				if ((error = libusb_interrupt_transfer(device_handle, 0x01, data, sizeof(data), &len, 0)) < 0)
					std::cout << "ERREUR " << libusb_strerror(error) << std::endl;

				//std::cout << "Data sent : " << outs[out[j][0]] << std::endl;
				std::cout << "Data sent : " << data << std::endl;

				//dev.write(0x1, outs[out[j][0]])

				// -----

				sleep(0.7f);
			}
		}
	}
	else
	{
		std::cout << "Not yet implemented" << std::endl;
	}
}

int main()
{
	std::cout << "FCU" << std::endl;
	
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("40", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16) });
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("42", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16) });
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("44", nullptr, 16), (unsigned int)std::stoi("4A", nullptr, 16), (unsigned int)std::stoi("BD", nullptr, 16) });
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("45", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16) });
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("46", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16) });
	outs.push_back({ (unsigned int)std::stoi("37", nullptr, 16), (unsigned int)std::stoi("4A", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16), (unsigned int)std::stoi("00", nullptr, 16) });
	
	/*outs.push_back({ 37, 40, 00, 00 });
	outs.push_back({ 37, 42, 00, 00 });
	outs.push_back({ 37, 44, 4A, BD });
	outs.push_back({ 37, 46, 00, 00 });
	outs.push_back({ 37, 48, 00, 00 });
	outs.push_back({ 37, 4A, 00, 80 });*/

	//outputs.append([nbData, index])
	outputs.push_back({ 1, 0 }); //CPT_FD
	outputs.push_back({ 1, 1 }); //PT_LS
	outputs.push_back({ 1, 2 }); //PT_CSTR
	outputs.push_back({ 1, 3 }); //PT_WPT
	outputs.push_back({ 1, 4 }); //PT_VOR
	outputs.push_back({ 1, 5 }); //PT_NDB
	outputs.push_back({ 1, 6 }); //PT_ARPT
	outputs.push_back({ 2, 7 }); //PT_QFE
	outputs.push_back({ 2, 9 }); //PT_QNH
	outputs.push_back({ 2, 11 }); //SPD
	outputs.push_back({ 2, 13 }); //MACH
	outputs.push_back({ 8, 15 }); //HDGVS
	outputs.push_back({ 8, 23 }); //TRKFPA
	outputs.push_back({ 1, 31 }); //HDGDOT
	outputs.push_back({ 1, 32 }); //ALTDOT
	outputs.push_back({ 1, 33 }); //SPDDOT
	outputs.push_back({ 1, 34 }); //AP1
	outputs.push_back({ 1, 35 }); //AP2
	outputs.push_back({ 1, 36 }); //ATHR
	outputs.push_back({ 1, 37 }); //LOC
	outputs.push_back({ 1, 38 }); //APPR
	outputs.push_back({ 1, 39 }); //EXPED
	outputs.push_back({ 1, 40 }); //CPT_FD
	outputs.push_back({ 1, 41 }); //CPT_LS
	outputs.push_back({ 1, 42 }); //CPT_CSTR
	outputs.push_back({ 1, 43 }); //CPT_WPT
	outputs.push_back({ 1, 44 }); //CPT_VOR
	outputs.push_back({ 1, 45 }); //CPT_NDB
	outputs.push_back({ 1, 46 }); //CPT_ARPT

	outputs.push_back({ 2, 47 }); //CPT_QFE
	outputs.push_back({ 2, 49 }); //CPT_QNH

	//outputs2.append([groupe, byte, bit])
	outputs2.push_back({ 3, 0, 0 }); //CPT_FD
	outputs2.push_back({ 3, 0, 1 }); //CPT_LS
	outputs2.push_back({ 3, 0, 4 }); //CPT_CSTR
	outputs2.push_back({ 3, 0, 2 }); //CPT_WPT
	outputs2.push_back({ 3, 0, 3 }); //CPT_VOR
	outputs2.push_back({ 3, 0, 6 }); //CPT_NDB
	outputs2.push_back({ 3, 0, 5 }); //CPT_ARPT
	outputs2.push_back({ 3, 1, 0 }); //CPT_QFE
	outputs2.push_back({ 3, 1, 1 }); //CPT_QFE
	outputs2.push_back({ 3, 1, 5 }); //CPT_QNH
	outputs2.push_back({ 3, 1, 6 }); //CPT_QNH
	outputs2.push_back({ 0, 0, 2 }); //SPD
	outputs2.push_back({ 0, 0, 3 }); //SPD

	outputs2.push_back({ 0, 0, 5 }); //MACH
	outputs2.push_back({ 0, 0, 6 }); //MACH
	outputs2.push_back({ 0, 0, 0 }); //HDGVS
	outputs2.push_back({ 0, 0, 1 }); //HDGVS
	outputs2.push_back({ 0, 1, 0 }); //HDGVS
	outputs2.push_back({ 0, 1, 1 }); //HDGVS
	outputs2.push_back({ 1, 1, 1 }); //HDGVS
	outputs2.push_back({ 1, 1, 6 }); //HDGVS
	outputs2.push_back({ 2, 0, 2 }); //HDGVS
	outputs2.push_back({ 2, 0, 4 }); //HDGVS
	outputs2.push_back({ 0, 1, 5 }); //TRKFPA
	outputs2.push_back({ 0, 1, 6 }); //TRKFPA
	outputs2.push_back({ 1, 1, 2 }); //TRKFPA
	outputs2.push_back({ 1, 1, 3 }); //TRKFPA
	outputs2.push_back({ 1, 1, 4 }); //TRKFPA
	outputs2.push_back({ 1, 1, 5 }); //TRKFPA
	outputs2.push_back({ 2, 0, 0 }); //TRKFPA
	outputs2.push_back({ 2, 0, 5 }); //TRKFPA
	outputs2.push_back({ 0, 1, 2 }); //HDGDOT
	outputs2.push_back({ 2, 1, 1 }); //ALTDOT
	outputs2.push_back({ 0, 0, 4 }); //SPDDOT
	outputs2.push_back({ 1, 0, 6 }); //AP1
	outputs2.push_back({ 1, 0, 4 }); //AP2
	outputs2.push_back({ 1, 0, 3 }); //ATHR
	outputs2.push_back({ 1, 0, 5 }); //LOC
	outputs2.push_back({ 1, 0, 1 }); //APPR
	outputs2.push_back({ 1, 0, 2 }); //EXPED
	outputs2.push_back({ 4, 1, 0 }); //FO_FD
	outputs2.push_back({ 4, 1, 1 }); //FO_LS
	outputs2.push_back({ 4, 1, 4 }); //FO_CSTR
	outputs2.push_back({ 4, 1, 6 }); //FO_WPT
	outputs2.push_back({ 4, 1, 3 }); //FO_VOR
	outputs2.push_back({ 4, 1, 2 }); //FO_NDB
	outputs2.push_back({ 4, 1, 5 }); //FO_ARPT
	outputs2.push_back({ 5, 1, 0 }); //FO_QFE
	outputs2.push_back({ 5, 1, 6 }); //FO_QFE
	outputs2.push_back({ 5, 1, 1 }); //FO_QNH
	outputs2.push_back({ 5, 1, 5 }); //FO_QNH

	std::iota(codeOUT.begin(), codeOUT.end(), 300);
	codeOUT.push_back(314);

	std::vector<unsigned int> temp(19);
	std::iota(temp.begin(), temp.end(), 322);
	codeOUT.insert(codeOUT.end(), temp.begin(), temp.end());

	int error = libusb_init(NULL);

	if (error != 0)
	{
		std::cout << libusb_strerror(error) << std::endl;
		return EXIT_FAILURE;
	}

	libusb_device** devices = NULL;
	libusb_device* fcu = NULL;
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

		if (hexVendor == "4d8" && hexProduct == "50")
		{
			std::cout << "fcu detected" << std::endl;
			fcu = devices[i];
			break;
		}
	}

	if (fcu)
	{
		libusb_device_handle* device_handle = NULL;

		error = libusb_open(fcu, &device_handle);

		if (error != 0)
			std::cout << "ERROR : " << libusb_strerror(error) << std::endl;

		if (device_handle)
		{
			std::cout << "Device opened" << std::endl;

			libusb_device_descriptor device_descriptor;
			error = libusb_get_device_descriptor(fcu, &device_descriptor);


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
			} while (length > 0);
			std::cout << "Done" << std::endl;
			
			output_sequence(true, true, device_handle);

			libusb_close(device_handle);
		}
	}

	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	std::cout << "Press enter to exit" << std::endl;
	std::cin.get();

	return 0;
}
