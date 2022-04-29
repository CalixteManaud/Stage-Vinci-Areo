import sys
import usb.core
import usb.util

# Connexion spécifique du OVERHEAD Panel
dev = usb.core.find(idVendor=0x04d8, idProduct=0x0070)

if dev is None:
    raise ValueError('Device is not found')

print(dev)

dev.set_configuration()

msg = ':SDSLSCPI#'
print("Write:", msg, dev.write(3, msg))

print("Read:", dev.read(0x81, 7))
