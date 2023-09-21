
# IMPORTAMOS LIBRERIAS 
import cv2 # Libreria OpenCV que se encarga del uso de la cámara
import numpy as np # Numpy para los array de los rangos de colores

import serial # Para la comunicación con el arduino
import os # Para limpiar la consola
import time # Para el manejo de tiempos


def clear_console(): # FUNCIÓN PARA LIMPIAR LA CONSOLA
    os.system('clear'if os.name=='posix'
              else 'cls')


# CONFIGURAR PUERTO SERIAL CON ARDUINO (Reemplaza el '/dev/ttyACM0' con el puerto que este usando el arduino)
ser = serial.Serial('/dev/ttyACM0', 9600)


# ABRIMOS LA CAMARA DEL RASPBERRY PI
cap = cv2.VideoCapture(0) # El '0' es por la cámara predeterminada


# VARIABLES CONTADORAS PARA EL ENVÍO DE MENSAJE AL ARDUINO
A = 0  # Mensaje para color GREEN
B = 0  # Mensaje para el color RED


# FUNCIÓN PARA LA COMUNICACIÓN DEL RASPBERRY CON ARDUINO
def send_command(command): # Se define la función con el nombre 'send_command'
    ser.write(command.encode()) # Envía el DATO al arduino
    time.sleep(1) # Tiempo de espera de ejecución del código para dar tiempo al arduino a recibir el comando


# RANGOS DE LOS COLORES HSV PARA LA DETECCIÓN
# PRIMER RANGO de color ROJO
RojoBajo1 = np.array([0, 100, 20], np.uint8)
RojoAlto1 = np.array([20, 255, 255], np.uint8)
# SEGUNDO RANGO de color ROJO
RojoBajo2 = np.array([160, 100, 20], np.uint8)
RojoAlto2 = np.array([179, 255, 255], np.uint8)

# PRIMER RANGO de color VERDE
VerdeBajo1 = np.array([40, 80, 80], np.uint8)
VerdeAlto1 = np.array([80, 255, 255], np.uint8)
# SEGUNDO RANGO de color VERDE
VerdeBajo2 = np.array([40, 100, 45], np.uint8)
VerdeAlto2 = np.array([80, 255, 255], np.uint8)


# VARIABLES PARA CONTAR CANTIDAD DE OBJETOS DETECTADOS
max_red_area = 0
max_red_contour = None
max_green_area = 0
max_green_contour = None


# BUCLE WHILE GENERAL PARA LA DETECCIÓN DE COLORES
while True:
    ret, frame = cap.read() # Lee los fotogramas desde la cámara 
    if ret == True: # En caso de que la lectura haya sido buena, realiza el siguiente bucle:
        frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) # Transformamos la lectura de color RGB en HSV

        # CREACIÓN DE MÁSCARAS DE COLOR ROJO
        MascaraRojo1 = cv2.inRange(frameHSV, RojoBajo1, RojoAlto1)
        MascaraRojo2 = cv2.inRange(frameHSV, RojoBajo2, RojoAlto2)
        MascaraRojo = cv2.add(MascaraRojo1, MascaraRojo2) # Juntamos ambas máscaras anteriores en una máscara

        # CREACIÓN DE MÁSCARAS DE COLOR VERDE
        MascaraVerde1 = cv2.inRange(frameHSV, VerdeBajo1, VerdeAlto1)
        MascaraVerde2 = cv2.inRange(frameHSV, VerdeBajo2, VerdeAlto2)
        MascaraVerde = cv2.add(MascaraVerde1, MascaraVerde2) # Juntamos ambas máscaras anteriores en una máscara


        #EROSIÓN A LA MÁSCARA VERDE PARA ELIMINAR FALSAS DETECCIONES
        kernel = np.ones((5, 5), np.uint8)
        MascaraVerde = cv2.erode(MascaraVerde, kernel, iterations = 1)


        # CREAMOS UNA MÁSCARA GENERAL PARA MOSTRAR LA DETECCIÓN DE AMBOS COLORES
        MascaraRojoVerde = cv2.add(MascaraRojo, MascaraVerde)


        # ENCUENTRA LOS CONTORNOS DE LOS OBJETOS DETECTADOS Y LOS GUARDA EN LA VARIABLE 'CONTOURS'
        contours, _ = cv2.findContours(MascaraRojoVerde, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # REINICIALIZAMOS LAS VARIABLES CONTADORAS DE DETECCIÓN
        max_red_area = 0
        max_red_contour = None
        max_green_area = 0
        max_green_contour = None


        for contour in contours: # Itera a través de todos los contornos detectados en el frame
            area = cv2.contourArea(contour) # Calcula el área del contorno en pixeles
            x, y, w, h = cv2.boundingRect(contour) # Calcula un rectángulo delimitador

            if area > 9000: # Si el área del contorno del objeto es mayor a 9000 pixeles, realiza la siguiente secuencia:
                if MascaraRojo[y + h // 2, x + w // 2] == 255 and area > max_red_area: # Verifica si el punto central del área detectada pertenece a la máscara rojo y si supera el area de color rojo máximo
                    max_red_area = area
                    max_red_contour = contour
                elif MascaraVerde[y + h // 2, x + w // 2] == 255 and area > max_green_area: # Verifica si el punto central del área detectada pertenece a la máscara verde y si supera el area de color verde máximo
                    max_green_area = area
                    max_green_contour = contour


        # DIBUJA UN RECTÁNGULO DEL CONTORNO DEL OBJETO ROJO CON ÁREA MÁS GRANDE
        if max_red_area > 0: # Verifica si se detectó un objeto color rojo con área mayor a 0
            x, y, w, h = cv2.boundingRect(max_red_contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2) # Dibuja un rectángulo alrededor del objeto de color rojo detectado
        
        # DIBUJA UN RECTÁNGULO DEL CONTORNO DEL OBJETO VERDE CON ÁREA MÁS GRANDE
        if max_green_area > 0:
            x, y, w, h = cv2.boundingRect(max_green_contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        
        # SI EL ÁREA EL OBJETO COLOR ROJO ES MAYOR A 9000 PIXELES, HACE EL SIGUIENTE BUCLE
        if max_red_area >= 9000:
            A = A + 1 # Contador para enviar cada cierto tiempo el DATO
            A1 = 30
            if A == A1: # Si el contador llega al límite, hace lo siguiente:
                print("Detectó ROJO") # Imprime en el monitor serial "Detectó ROJO"
                send_command('H') # Envía al Arduino el comando 'H'
                A = 0 # Reinicia el contador

        # SI EL ÁREA EL OBJETO COLOR ROJO ES MAYOR A 9000 PIXELES, HACE EL SIGUIENTE BUCLE
        if max_green_area >= 9000:
            B = B + 1 # Contaodr para enviar cada cierto tiempo el DATO
            B1 = 30
            if B == B1: # Si el contador llega al límite, hace lo siguiente:
                print("Detectó VERDE") # Imprime en el monitor serial "Detectó VERDE"
                send_command('L') # Envía al arduino el comando 'L'
                B = 0 # Reinicia el contador
        

        # MUESTRA LAS MÁSCARAS COMBINADAS Y OBJETOS DETECTADOS EN UNA VENTANA
        cv2.imshow('Máscaras combinadas y detección de objetos', frame)


        # SE INTERRUMPE EL BUCLE DEL PROGRAMA PRESIONANDO LA TECLA 'S'
        if cv2.waitKey(1) & 0xFF == ord('s'): 
            break

cap.release()
cv2.destroyAllWindows()
