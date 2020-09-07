import dht
import machine
while True:
    d = dht.DHT11(machine.Pin(2))
    d.measure()
    temp = d.temperature() # eg. 23 (閹虹煰)
    humid = d.humidity()    # eg. 41 (% RH)
    print('Temperature :',temp,'Humidity' , humid)
"""
d = dht.DHT22(machine.Pin(4))
d.measure()
d.temperature() # eg. 23.6 (閹虹煰)
d.humidity()    # eg. 41.3 (% RH)"""
