# Importamos librerias necesarias
import cv2 # Libreria OpenCV que se encarga del uso y administracion de la camara, imagenes o videos
import numpy as np #Numpy para los array para los rango de colores
import time
import serial
import os


def clear_console(): #Funcion para limpiar la consola
    os.system('clear'if os.name=='posix'
              else 'cls')
# Configura el puerto serial (reemplaza '/dev/ttyACM0' con el nombre del puerto donde va a ir el arduino)
ser = serial.Serial('/dev/ttyACM0', 9600)

#Abrimos la camara de la computadora
cap = cv2.VideoCapture(0)

# Definir el número de pin GPIO al que está conectado el LED
pin_led = 26

#Variable para mensaje unico hacia el arduino GREEN
A=0
#Variable unica para arduino RED
B=0

#Funcion de la comunicacion del raspberry con el arduino 
def send_command(command): #Se define funcion con el nombre
    ser.write(command.encode()) # Envia el comando al Arduino
    time.sleep(1) # TTiempo de espera a que el arduino procese el dato enviado


# Rangos de deteccion del color verde en HSV (rango 1 de color rojo)
redBajo1 = np.array([0, 100, 20], np.uint8)
redAlto1 = np.array([20, 255, 255], np.uint8)

# (rango 2 de color rojo)
redBajo2 = np.array([160, 100, 20], np.uint8)
redAlto2 = np.array([179, 255, 255], np.uint8)

# Rangos de deteccion del color verde en HSV (rango 1 de color verde)
greenBajo = np.array([90, 50, 50], np.uint8)  
greenAlto = np.array([130, 255, 255], np.uint8)

# (rango 2 de color verde - claro)
greenBajo_darker = np.array([90, 50, 50], np.uint8)  
greenAlto_darker = np.array([130, 255, 255], np.uint8)

# Variables para mantener el registro de los objetos detectados
max_red_area = 0
max_red_contour = None
max_green_area = 0
max_green_contour = None

# Bucle raiz para el codigo de deteccion de colores
while True:

    # Lee los fotogramas desde la camara y detecta si la lectura fue buena o no
    ret, frame = cap.read()
    if ret == True: # En caso de que la lectura haya sido buena: 
        frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) #Como OpenCV solo trabaja con el modelo de color HSV debemos pasar la deteccion de color RGB a HSV

        # Creamos las mascaras del color rojo con los rangos rojos definidos anteriormente
        maskRed1 = cv2.inRange(frameHSV, redBajo1, redAlto1)
        maskRed2 = cv2.inRange(frameHSV, redBajo2, redAlto2)
        maskRed = cv2.add(maskRed1, maskRed2)

        # Creamos las mascaras del color verde claro con los rangos definidos anteriormente
        maskGreen_light = cv2.inRange(frameHSV, greenBajo, greenAlto)
        # Creamos las mascaras del color verde oscuro con los rangos definidos anteriormente
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
            area = cv2.contourArea(contour) # Calcula el area del contorno detectado, lee el area en pixeles
            x, y, w, h = cv2.boundingRect(contour) # Calcula el rectangulo delimitador alrededor del contorno.

            if area > 9000: # Si el area del contorno del objeto detectado es mayor a 9000 pixeles:
                if maskRed[y + h // 2, x + w // 2] == 255 and area > max_red_area: # Verifica si el punto central del area detectada pertenece a la mascara de color rojo y supera el area de color rojo maximo
                    max_red_area = area
                    max_red_contour = contour
                elif maskGreen[y + h // 2, x + w // 2] == 255 and area > max_green_area: #Verifica si el punto central de area detectada a la mascara del color verde pertenece a la mascara de color verde y si supera el area de color verde maximo
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
        if max_red_area >= 9000:
            A = A + 1
            A1 = 5
            if A == A1:
                print ("Regresar")
                send_command('H') # ROJO
                A = 0
        
        if max_green_area>=9000:
            B = B + 1
            B1 = 5
            if B == B1:
                print ("Esquivar")
                send_command('L') # VERDE
                B = 0
            
        # Mostrar las máscaras combinadas y los objetos detectados en una ventana
        cv2.imshow('Combined Masks and Detected Objects', frame)

        if cv2.waitKey(1) & 0xFF == ord('s'):
            break
        
        
cap.release()
cv2.destroyAllWindows()
