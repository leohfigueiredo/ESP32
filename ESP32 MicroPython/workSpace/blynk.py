3
4
5
6
7
8
	
from machine import Pin
from time import sleep
 
led = Pin(2, Pin.OUT)
 
while True:
    led.value(not led.value())
    sleep(1.0)
