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


/*std::vector<std::vector<unsigned int>> outputsOfCode(unsigned int code)
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
}*/

int main()
{
	std::cout << "FCU" << std::endl;
	
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
			
			//output_sequence(true, true, device_handle);

			for(unsigned int l = 0; l < 40000; l++)
			{
				//libusb_transfer* transfer = libusb_alloc_transfer(0);

				unsigned char data[512];
				int len = 0;
				if((error = libusb_interrupt_transfer(device_handle, 0x82, data, sizeof(data), &len, 0)) < 0)
					std::cout << "ERREUR " << libusb_strerror(error) << std::endl;
				//0x82 in
				//0x01 out

				for(unsigned int i = 0; i < len; i++)
					std::cout << (int)data[i] << ' ';
				std::cout << std::endl;

				/*
				
				// exemple: 54 73 127 255
				// 54 ne change jamais, on ne le récupère pas

				// data[1] : 65, 67, 69, 71, 73, 75
				// data[2] : 190, 189, 187, 183, 175, 223, 191, 127, 254, 253, 251, 239, 207, 126, 125, 123, 119, 111, 247, 219, 221
				// data[3] : 143, 151, 223, 159, 127, 191, 155, 157, 252, 253, 254, 199, 247, 231, 135, 243, 211, 227

				std::string button;

				// Left joystick
				if(data[1] == 67 && data[2] == 223 && data[3] == 255)
					button = "ljoystickpress";
				else if(data[1] == 67 && data[2] == 223 && data[3] == 191)
					button = "ljoystickturn1";
				else if(data[1] == 67 && data[2] == 223 && data[3] == 223)
					button = "ljoystickturn2";
				else if(data[1] == 67 && data[2] == 255 && data[3] == 159)
					button = "ljoystickselect";

				// Right joystick
				else if(data[1] == 75 && data[2] == 223 && data[3] == 255)
					button = "rjoystickpress";
				else if(data[1] == 75 && data[2] == 223 && data[3] == 247)
					button = "rjoystickturn1";
				else if(data[1] == 75 && data[2] == 223 && data[3] == 251)
					button = "rjoystickturn2";
				else if(data[1] == 75 && data[2] == 255 && data[3] == 243)
					button = "rjoystickselect";

				// Left switches
				else if(data[1] == 67 && data[2] == 223 && data[3] == 155 ||
				data[1] == 67 && data[2] == 223 && data[3] == 250 ||
				data[1] == 67 && data[2] == 223 && data[3] == 251)
					button = "lswitch1left";
				else if(data[1] == 67 && data[2] == 223 && data[3] == 254 ||
				data[1] == 67 && data[2] == 223 && data[3] == 255)
					button = "lswitch1middle";
				else if(data[1] == 67 && data[2] == 223 && data[3] == 252 ||
				data[1] == 67 && data[2] == 223 && data[3] == 253)
					button = "lswitch1right";
				else if(data[1] == 69 && data[2] == 127 && data[3] == 255)
					button = "lswitch2left";
				else if(data[1] == 69 && data[2] == 255 && data[3] == 255)
					button = "lswitch2middle";
				else if(data[1] == 69 && data[2] == 191 && data[3] == 255)
					button = "lswitch2right";

				// Right switches
				else if(data[1] == 71 && data[2] == 203 && data[3] == 247)
					button = "rswitch1left";
				else if(data[1] == 71 && data[2] == 207 && data[3] == 247)
					button = "rswitch1middle";
				else if(data[1] == 71 && data[2] == 199 && data[3] == 247)
					button = "rswitch1right";
				else if(data[1] == 75 && data[2] == 221 && data[3] == 243)
					button = "rswitch2left";
				else if(data[1] == 75 && data[2] == 223 && data[3] == 243)
					button = "rswitch2middle";
				else if(data[1] == 75 && data[2] == 219 && data[3] == 243)
					button = "rswitch2right";

				// Middle buttons
				else if(data[1] == 69 && data[2] == 254 && data[3] == 255)
					button = "spdmach";
				else if(data[1] == 69 && data[2] == 253 && data[3] == 255)
					button = "hdgtrkv/sfpa";
				//else if(data[1] == 69 && data[2] == 253 && data[3] == 255)
				//	button = "metricalt";
				else if(data[1] == 69 && data[2] == 247 && data[3] == 255)
					button = "loc";
				else if(data[1] == 69 && data[2] == 239 && data[3] == 255)
					button = "ap1";
				else if(data[1] == 69 && data[2] == 223 && data[3] == 255)
					button = "ap2";
				else if(data[1] == 69 && data[2] == 251 && data[3] == 255)
					button = "a/thr";
				else if(data[1] == 71 && data[2] == 253 && data[3] == 247)
					button = "exped";
				else if(data[1] == 71 && data[2] == 254 && data[3] == 247)
					button = "appr";
				
				// Center joysticks
				else if(data[1] == 69 && data[2] == 255 && data[3] == 251)
					button = "cjoystick1press";
				else if(data[1] == 69 && data[2] == 255 && data[3] == 253)
					button = "cjoystick1turn1";
				else if(data[1] == 69 && data[2] == 255 && data[3] == 254)
					button = "cjoystick1turn2";
				//else if(data[1] == 69 && data[2] == 255 && data[3] == 251)
				//	button = "cjoystick2press";
				else if(data[1] == 69 && data[2] == 255 && data[3] == 220)
					button = "cjoystick2turn1";
				else if(data[1] == 69 && data[2] == 255 && data[3] == 236)
					button = "cjoystick2turn2";
				else if(data[1] == 71 && data[2] == 79 && data[3] == 199)
					button = "cjoystick3press";
				else if(data[1] == 71 && data[2] == 223 && data[3] == 199)
					button = "cjoystick3turn1";
				else if(data[1] == 71 && data[2] == 229 && data[3] == 199)
					button = "cjoystick3turn2";
				else if(data[1] == 71 && data[2] == 207 && data[3] == 207)
					button = "cjoystick3select";
				else if(data[1] == 71 && data[2] == 207 && data[3] == 199)
					button = "cjoystick4press";
				else if(data[1] == 71 && data[2] == 207 && data[3] == 215)
					button = "cjoystick4turn1";
				else if(data[1] == 71 && data[2] == 207 && data[3] == 231)
					button = "cjoystick4turn2";

				// Bottom left buttons
				else if(data[1] == 67 && data[2] == 223 && data[3] == 142 ||
				data[1] == 67 && data[2] == 223 && data[3] == 238)
					button = "lfd";
				else if(data[1] == 67 && data[2] == 223 && data[3] == 151 ||
				data[1] == 67 && data[2] == 223 && data[3] == 246)
					button = "lils";			

				// Left buttons
				else if(data[1] == 65 && data[2] == 254 && data[3] == 251 ||
				data[1] == 65 && data[2] == 254 && data[3] == 219 ||
				data[1] == 65 && data[2] == 254 && data[3] == 123 ||
				data[1] == 65 && data[2] == 254 && data[3] == 187 ||
				data[1] == 65 && data[2] == 254 && data[3] == 235 ||
				data[1] == 65 && data[2] == 126 && data[3] == 239 ||
				data[1] == 65 && data[2] == 190 && data[3] == 239 ||
				data[1] == 65 && data[2] == 222 && data[3] == 239 ||
				data[1] == 65 && data[2] == 254 && data[3] == 237 ||
				data[1] == 65 && data[2] == 254 && data[3] == 238 ||
				data[1] == 65 && data[2] == 254 && data[3] == 190 ||
				data[1] == 65 && data[2] == 254 && data[3] == 126 ||
				data[1] == 65 && data[2] == 254 && data[3] == 222 ||
				data[1] == 65 && data[2] == 254 && data[3] == 254 ||
				data[1] == 65 && data[2] == 254 && data[3] == 253 ||
				data[1] == 65 && data[2] == 254 && data[3] == 221 ||
				data[1] == 65 && data[2] == 254 && data[3] == 125 ||
				data[1] == 65 && data[2] == 254 && data[3] == 189)
					button = "lcstr";
				else if(data[1] == 65 && data[2] == 221 && data[3] == 127)
					button = "lwpt";
				else if(data[1] == 65 && data[2] == 219 && data[3] == 127)
					button = "lvor.d";
				else if(data[1] == 65 && data[2] == 215 && data[3] == 127)
					button = "lndb";
				else if(data[1] == 65 && data[2] == 207 && data[3] == 127)
					button = "larpt";

				// Bottom right buttons
				else if(data[1] == 75 && data[2] == 223 && data[3] == 227)
					button = "rfd";
				else if(data[1] == 75 && data[2] == 223 && data[3] == 211)
					button = "rils";
				
				// Right buttons
				else if(data[1] == 73 && data[2] == 175 && data[3] == 127)
					button = "rcstr";
				else if(data[1] == 73 && data[2] == 183 && data[3] == 127)
					button = "rwpt";
				else if(data[1] == 73 && data[2] == 187 && data[3] == 127)
					button = "rvor.d";
				else if(data[1] == 73 && data[2] == 189 && data[3] == 127)
					button = "rndb";
				else if(data[1] == 73 && data[2] == 190 && data[3] == 127)
					button = "rarpt";
				
				// Left selectors
				else if(data[1] == 65 && data[2] == 223 && data[3] == 255 ||
				data[1] == 65 && data[2] == 255 && data[3] == 251)
					button = "lselector1turn";
				else if(data[1] == 65 && data[2] == 255 && data[3] == 255)
					button = "lselector2turn";
				
				// Right selectors
				else if(data[1] == 73 && data[2] == 255 && data[3] == 127)
					button = "rselector1turn";
				else if(data[1] == 73 && data[2] == 255 && data[3] == 251)
					button = "rselector2turn";
				
				else
					button = "unknown";

				if(button != "unknown")
					std::cout << button << std::endl;

				*/
			}

			libusb_close(device_handle);
		}
	}

	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	std::cout << "Press enter to exit" << std::endl;
	std::cin.get();

	return 0;
}
