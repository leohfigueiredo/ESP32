import machine
import utime

pin2 = machine.Pin(2,machine.Pin.OUT)

while True:
pin2.value(1)
utime.sleep_ms(1000)
pin2.value(0)
utime.sleep_ms(1000)
