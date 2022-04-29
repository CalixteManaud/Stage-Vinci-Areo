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

dev.set_configuration()

cfg = dev.get_active_configuration()
intf = cfg[(0, 0)]

ep = usb.util.find_descriptor(
    intf,

    custom_match= \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointintAddress) == \
        usb.util.ENDPOINT_OUT)

assert ep is not None

ep.write('test')