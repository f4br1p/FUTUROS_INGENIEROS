import cv2
import numpy as np
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

cap = cv2.VideoCapture(0)

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

# Ampliamos el rango de detección del color rojo en HSV
redBajo1 = np.array([0, 100, 20], np.uint8)
redAlto1 = np.array([20, 255, 255], np.uint8)

redBajo2 = np.array([160, 100, 20], np.uint8)
redAlto2 = np.array([179, 255, 255], np.uint8)

greenBajo = np.array([40, 80, 80], np.uint8)  # Adjust the values here for lighter green
greenAlto = np.array([80, 255, 255], np.uint8)

# Rango de detección del color verde en HSV (darker green)
greenBajo_darker = np.array([40, 100, 45], np.uint8)  # Adjust the values here for darker green
greenAlto_darker = np.array([80, 255, 255], np.uint8)

# Variables para mantener el registro de los objetos detectados
max_red_area = 0
max_red_contour = None
max_green_area = 0
max_green_contour = None

while True:
    ret, frame = cap.read()
    if ret == True:
        frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Creamos las máscaras para detectar el rango ampliado del color rojo
        maskRed1 = cv2.inRange(frameHSV, redBajo1, redAlto1)
        maskRed2 = cv2.inRange(frameHSV, redBajo2, redAlto2)
        maskRed = cv2.add(maskRed1, maskRed2)

        # Creamos la máscara para detectar el color verde (lighter green)
        maskGreen_light = cv2.inRange(frameHSV, greenBajo, greenAlto)
        # Creamos la máscara para detectar el color verde (darker green)
        maskGreen_darker = cv2.inRange(frameHSV, greenBajo_darker, greenAlto_darker)
        # Creamos la mascara para detectar ambos rangos
        maskGreen = cv2.add(maskGreen_light, maskGreen_darker)

        # Aplicar erosión a la máscara verde para eliminar falsas detecciones
        kernel = np.ones((5, 5), np.uint8)
        maskGreen = cv2.erode(maskGreen, kernel, iterations=1)

        # Unimos las máscaras de rojo y verde para mostrar ambos colores
        maskRedAndGreen = cv2.add(maskRed, maskGreen)

        # Encontrar los contornos de los objetos con color rojo o verde y área mayor a 5000
        contours, _ = cv2.findContours(maskRedAndGreen, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Restablecer las variables de detección
        max_red_area = 0
        max_red_contour = None
        max_green_area = 0
        max_green_contour = None

        for contour in contours:
            area = cv2.contourArea(contour)
            x, y, w, h = cv2.boundingRect(contour)

            if area > 5000:
                if maskRed[y + h // 2, x + w // 2] == 255 and area > max_red_area:
                    max_red_area = area
                    max_red_contour = contour
                elif maskGreen[y + h // 2, x + w // 2] == 255 and area > max_green_area:
                    max_green_area = area
                    max_green_contour = contour

        # Dibujar el contorno del objeto rojo con el área más grande
        if max_red_area > 0:
            x, y, w, h = cv2.boundingRect(max_red_contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)

        # Dibujar el contorno del objeto verde con el área más grande
        if max_green_area > 0:
            x, y, w, h = cv2.boundingRect(max_green_contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Imprimir en la terminal la acción correspondiente al color con el área más grande
        if max_red_area > 5000:
            print("Detenerse")
            encender_led()
        elif max_green_area > 5000:
            print("Avanzar")
            apagar_led()

        # Mostrar las máscaras combinadas y los objetos detectados en una ventana
        cv2.imshow('Combined Masks and Detected Objects', frame)

        if cv2.waitKey(1) & 0xFF == ord('s'):
            break

cap.release()
cv2.destroyAllWindows()
