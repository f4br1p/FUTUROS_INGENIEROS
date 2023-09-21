import cv2
import numpy as np

def nothing(x):
    pass

# Definimos el puerto de la cámara a emplear         
cap = cv2.VideoCapture(0)

# Creamos una ventana para mostrar la imagen
cv2.namedWindow('Captura de video')

# Creamos controles deslizantes para ajustar los rangos de color
cv2.createTrackbar('Hue Min', 'Captura de video', 0, 179, nothing)
cv2.createTrackbar('Hue Max', 'Captura de video', 179, 179, nothing)
cv2.createTrackbar('Sat Min', 'Captura de video', 0, 255, nothing)
cv2.createTrackbar('Sat Max', 'Captura de video', 255, 255, nothing)
cv2.createTrackbar('Val Min', 'Captura de video', 0, 255, nothing)
cv2.createTrackbar('Val Max', 'Captura de video', 255, 255, nothing)

# Mientras está activada la captura de video
while True:
    # Obtenemos un valor booleano e imagen
    ret, frame = cap.read()

    # Si hay imagen capturada
    if ret == True:
        # Convertimos la imagen BGR a HSV
        frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        # Obtenemos los valores actuales de los controles deslizantes
        hue_min = cv2.getTrackbarPos('Hue Min', 'Captura de video')
        hue_max = cv2.getTrackbarPos('Hue Max', 'Captura de video')
        sat_min = cv2.getTrackbarPos('Sat Min', 'Captura de video')
        sat_max = cv2.getTrackbarPos('Sat Max', 'Captura de video')
        val_min = cv2.getTrackbarPos('Val Min', 'Captura de video')
        val_max = cv2.getTrackbarPos('Val Max', 'Captura de video')

        # Definimos los rangos de color en HSV
        verdeBajo = np.array([hue_min, sat_min, val_min], np.uint8)
        verdeAlto = np.array([hue_max, sat_max, val_max], np.uint8)

        # Creamos una máscara para el color verde en el rango especificado
        maskVerde = cv2.inRange(frameHSV, verdeBajo, verdeAlto)

        # Mostramos la ventana de captura
        cv2.imshow('Captura de video', frame)
        cv2.imshow('Mascara Verde', maskVerde)

        # Detenemos la visualización con la tecla 's'
        if cv2.waitKey(1) & 0xFF == ord('s'):
            break

# Detenemos la captura de video
cap.release()
# Cerramos todas las ventanas
cv2.destroyAllWindows()
