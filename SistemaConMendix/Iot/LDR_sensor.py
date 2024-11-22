"""
This ESP32 MicroPython code was developed by newbiely.com
This ESP32 MicroPython code is made available for public use without any restriction
For comprehensive instructions and wiring diagrams, please visit:
https://newbiely.com/tutorials/esp32-micropython/esp32-micropython-ldr-module
"""

from machine import Pin
import utime  # For timing functions
from time import sleep

pir_pin = Pin(2, Pin.IN)  # Configura el pin 2 como entrada

DO_PIN = Pin(23, Pin.IN)  # The ESP32 pin GPIO13 connected to the DO pin of the LDR module

while True:
    light_state = DO_PIN.value()  # Read the digital value from the pin

    if light_state == 1:
        print("The light is NOT present")
    else:
        print("The light is present")

    utime.sleep(0.5)  # Add a small delay to avoid spamming the output

