import RPi.GPIO as GPIO
import time

# Establecer el modo de pines GPIO (BCM o BOARD)
GPIO.setmode(GPIO.BCM)

# Definir el número de pin GPIO al que está conectado el LED
pin_led = 26
# Configurar el pin GPIO como salida
GPIO.setup(pin_led, GPIO.OUT)

# Función para encender el LED
def encender_led():
    GPIO.output(pin_led, GPIO.HIGH)

# Función para apagar el LED
def apagar_led():
    GPIO.output(pin_led, GPIO.LOW)

try:
    while True:
        # Encender el LED
        encender_led()
        time.sleep(1)  # Esperar 1 segundo

        # Apagar el LED
        apagar_led()
        time.sleep(1)  # Esperar 1 segundo

except KeyboardInterrupt:
    # Si se presiona Ctrl + C, limpiar y salir
    GPIO.cleanup()
