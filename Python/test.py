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

while True:
    try:
        data = dev.read(0x82, 8, 500)
        print(data)
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
