from machine import Pin
from time import sleep_ms
import network
import urequests
import json
import utime

# Configuración de los pines del ULN2003 conectados al 28BYJ-48
IN1 = Pin(5, Pin.OUT)   # D5
IN2 = Pin(18, Pin.OUT)  # D18
IN3 = Pin(19, Pin.OUT)  # D19
IN4 = Pin(21, Pin.OUT)  # D21

# Secuencia de pasos para el motor 28BYJ-48
steps = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1]
]

# Configuración Wi-Fi
ssid = "OnePlus"          # Cambiar al SSID correcto
password = "juan1234"     # Cambiar a la contraseña correcta
url_pir = "http://dtai.uteq.edu.mx/~corjua228/awos/iot/pir_service.php"  # URL para datos del PIR
url_ldr = "http://dtai.uteq.edu.mx/~corjua228/awos/iot/ldr_service.php"  # URL para datos del LDR

# Conectar al Wi-Fi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

timeout = 20
while not wlan.isconnected() and timeout > 0:
    utime.sleep(1)
    timeout -= 1

# Configuración de los pines de los sensores
pir_pin = Pin(2, Pin.IN)       # Sensor PIR en el pin 2
ldr_pin = Pin(23, Pin.IN)      # Sensor LDR en el pin 23 (DO_PIN)

# Variables para el movimiento continuo del motor
step_index = 0
delay_motor = 1  # Ajusta este valor para cambiar la velocidad del motor

# Función para mover un solo paso del motor
def move_step():
    global step_index
    current_step = steps[step_index]
    IN1.value(current_step[0])
    IN2.value(current_step[1])
    IN3.value(current_step[2])
    IN4.value(current_step[3])
    step_index = (step_index + 1) % len(steps)  # Ciclo continuo en pasos

# Función para enviar datos de sensores al servidor
def send_sensor_data():
    try:
        headers = {'Content-Type': 'application/json'}
        
        # Leer el estado del sensor PIR
        movimiento = pir_pin.value()
        if movimiento == 1:  # Detecta movimiento
            data_pir = '{"value": "Movimiento detectado"}'
            print("Movimiento detectado!")
            response_pir = urequests.post(url_pir, data=data_pir, headers=headers)
            response_pir.close()

        # Leer el estado del sensor LDR
        luz_presente = ldr_pin.value()  # 0 indica luz presente, 1 indica luz no detectada
        if luz_presente == 1:
            data_ldr = '{"value": "Luz no detectada"}'
            print("Luz no detectada!")
            response_ldr = urequests.post(url_ldr, data=data_ldr, headers=headers)
            response_ldr.close()

    except Exception as e:
        print("Error al enviar datos:", e)

# Bucle principal que mueve el motor y envía datos de los sensores
while wlan.isconnected():
    move_step()             # Mueve el motor continuamente
    sleep_ms(delay_motor)   # Controla la velocidad del motor

    # Enviar datos cada 10 segundos
    if utime.time() % 10 == 0:
        send_sensor_data()
