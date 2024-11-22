import network
import urequests
import time
import json

# Configuración de la red Wi-Fi
ssid = "OnePlus"          # Reemplaza con tu SSID
password = "juan1234"     # Reemplaza con tu contraseña

# Conectar al Wi-Fi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
time.sleep(1)

try:
    print("Conectando a Wi-Fi...")
    wlan.connect(ssid, password)

    # Espera a que se establezca la conexión (puedes aumentar el tiempo de espera)
    timeout = 20  # Timeout en segundos
    while not wlan.isconnected() and timeout > 0:
        time.sleep(1)
        timeout -= 1
    
    if wlan.isconnected():
        print("Conectado a Wi-Fi:", wlan.ifconfig())
    else:
        print("No se pudo conectar a Wi-Fi.")
        
except Exception as e:
    print("Error al conectar a Wi-Fi:", e)

# URL del script PHP en tu servidor
url = "http://dtai.uteq.edu.mx/~corjua228/awos/iot/pruebas.php"

# Mantener el microcontrolador encendido y enviar datos
while wlan.isconnected():
    try:
        # Crear el JSON a enviar
        data = {
            "value": "Hola, Mundo"
        }
        headers = {'Content-Type': 'application/json'}

        # Convertir el diccionario a JSON
        json_data = json.dumps(data)

        # Enviar "Hola, Mundo" a la API
        response = urequests.post(url, data=json_data, headers=headers)
        print("Respuesta del servidor:", response.text)
        response.close()
        
    except Exception as e:
        print("Error al enviar datos:", e)

    time.sleep(10)  # Esperar 10 segundos antes de enviar de nuevo
