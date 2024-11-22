from machine import Pin
from time import sleep

# Configuración del pin del sensor PIR
pir_pin = Pin(2, Pin.IN)  # Configura el pin 2 como entrada

while True:
    if pir_pin.value() == 1:  # Si el PIR detecta movimiento (HIGH)
        print("Movimiento detectado!")
        sleep(1)  # Espera 5 segundos antes de verificar nuevamente
    else:
        print("Sin movimiento detectado")
    
    sleep(0.5)  # Pequeño retardo para evitar lecturas excesivas
