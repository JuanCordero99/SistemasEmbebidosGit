from machine import Pin
from time import sleep

# Pines del ULN2003 conectados al 28BYJ-48
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

# Función para mover el motor en una dirección
def move_stepper(steps, delay, direction):
    for step in range(8) if direction == "clockwise" else range(7, -1, -1):
        IN1.value(steps[step][0])
        IN2.value(steps[step][1])
        IN3.value(steps[step][2])
        IN4.value(steps[step][3])
        sleep(delay)

# Configuración principal del movimiento
def rotate_motor(rotations, delay, direction="clockwise"):
    for _ in range(rotations):
        move_stepper(steps, delay, direction)

# Ejemplo de uso
# Gira 512 pasos (una vuelta completa) en sentido horario con un retardo de 2 ms entre pasos
rotate_motor(512*4, 0.001, "clockwise")

# Gira 512 pasos (una vuelta completa) en sentido antihorario con un retardo de 2 ms entre pasos
# rotate_motor(512, 0.002, "counterclockwise")
