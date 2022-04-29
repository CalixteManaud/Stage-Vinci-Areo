import sys
import usb.core
import usb.util

# Connexion spécifique du OVERHEAD Panel
dev = usb.core.find(idVendor=0x04d8, idProduct=0x0070)

if dev is None:
    raise ValueError('Device is not found')
else:
    print(dev)
    dev.set_configuration()


def send(cmd):
    dev.write(3, cmd)
    result = (dev.read(0x81, 100000, 1000))
    return result


def get_id():
    return send('*IDN?').tobytes().decode('utf-8')


def get_data(ch):
    rawdata = send(':DATA:WAVE:SCREen:CH{}?'.format(ch))
    data = []
    for idx in range(4, len(rawdata), 2):
        point = int().from_bytes([rawdata[idx], rawdata[idx + 1]], 'little', signed=True)
        data.append(point / 4096)
    return data


def get_header():
    header = send(':DATA:WAVE:SCREen:HEAD?')
    header = header[4:].tobytes.decode('utf-8')
    return header


def save_data(ffname, data):
    f = open(ffname, 'w')
    f.write('\n'.join(map(str, data)))
    f.close()


print(get_id())
header = get_header()
data = get_data(1)
save_data('Osci.dat', data)
