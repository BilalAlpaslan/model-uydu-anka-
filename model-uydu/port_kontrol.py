#                ---PORT KONTROL---

import sys, serial, serial.tools.list_ports, time

#port tespit etme - baslangic       #
ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if 'USB' in p.description
    ]

if not ports:
    raise IOError("Seri Baglantili cihaz yok!")
else:
  ser = serial.Serial(ports[0],9600)
#port tespit etme - son          

print(ports)