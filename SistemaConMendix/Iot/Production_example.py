import network
import urequests
import json
from machine import Pin
import utime
import Stpper_motor

# Configuración Wi-Fi

rotate_motor(512*40, 0.001, "clockwise")

ssid = "OnePlus"          # Cambiar al SSID correcto
password = "juan1234"     # Cambiar a la contraseña correcta
url_pir = "http://dtai.uteq.edu.mx/~corjua228/awos/iot/pir_service.php"  # URL para datos del PIR
url_ldr = "http://dtai.uteq.edu.mx/~corjua228/awos/iot/ldr_service.php"  # URL para datos del LDR

# Configurar Wi-Fi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
utime.sleep(1)

try:
    print("Conectando a Wi-Fi...")
    wlan.connect(ssid, password)

    # Espera a que se establezca la conexión
    timeout = 20
    while not wlan.isconnected() and timeout > 0:
        utime.sleep(1)
        timeout -= 1

    if wlan.isconnected():
        print("Conectado a Wi-Fi:", wlan.ifconfig())
    else:
        print("No se pudo conectar a Wi-Fi.")

except Exception as e:
    print("Error al conectar a Wi-Fi:", e)

# Configuración de los pines de los sensores
pir_pin = Pin(2, Pin.IN)       # Sensor PIR en el pin 2
ldr_pin = Pin(23, Pin.IN)      # Sensor LDR en el pin 23 (DO_PIN)

# Mantener el dispositivo activo y enviar datos
while wlan.isconnected():
    try:
        headers = {'Content-Type': 'application/json'}

        # Leer el estado del sensor PIR
        movimiento = pir_pin.value()
        if movimiento == 1:  # Detecta movimiento
            # Crear datos en formato JSON con la cadena completa para el sensor PIR
            data_pir = '{"value": "Movimiento detectado"}'
            print("Movimiento detectado!")  # Mensaje en la terminal
            print("Enviando datos del PIR:", data_pir)  # Mensaje antes de enviar
            
            response_pir = urequests.post(url_pir, data=data_pir, headers=headers)
            print("Respuesta del servidor (PIR):", response_pir.text)
            response_pir.close()

        # Leer el estado del sensor LDR
        luz_presente = ldr_pin.value()  # 0 indica luz presente, 1 indica luz no detectada
        if luz_presente == 1:  # Solo cuando no hay luz
            # Crear datos en formato JSON con la cadena completa para el sensor LDR
            data_ldr = '{"value": "Luz no detectada"}'
            print("Luz no detectada!")  # Mensaje en la terminal
            print("Enviando datos del LDR:", data_ldr)  # Mensaje antes de enviar
            
            response_ldr = urequests.post(url_ldr, data=data_ldr, headers=headers)
            print("Respuesta del servidor (LDR):", response_ldr.text)
            response_ldr.close()

    except Exception as e:
        print("Error al enviar datos:", e)

    utime.sleep(10)  # Esperar 10 segundos antes de la siguiente lectura y envío
