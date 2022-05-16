import sys
import usb
import usb.core
import usb.util

# Connexion spécifique du OVERHEAD Panel
dev = usb.core.find(idVendor=0x04d8, idProduct=0x0070)

interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

if dev is None:
    raise ValueError('Device not found')
    sys.exit(1)

read_data = []

while True:
    try:
        data = dev.read(0x82, 8, 500)
        print("Read: ", data)
        print("Write: ", dev.write(1, '0x81'))
        print(bin(data[2]))
        print(bin(data[3]))
        read_data.append([data[2], data[3]])
        print(read_data)
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
