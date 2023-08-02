
# Empezamos incluyendo las librerías a emplear
import cv2
import numpy as np

# Definimos una función para detectar colores y graficar contornos
def draw(mask, color):
    contornos,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    for c in contornos:
        area = cv2.contourArea(c)
        
        # Si el área de interés es mayor a
        if area > 5000:    
            M = cv2.moments(c)
            if (M["m00"] == 0):
                M["m00"] = 1
                
            x = int(M["m10"]/M["m00"])
            y = int(M["m01"]/M["m00"])
            
            #--- Dibujamos los contornos seleccionados ---
            newContorno = cv2.convexHull(c)
             
            #--- Dibujamos un punto de r=7 y color verde ---
            cv2.circle(frame, (x, y), 7, (0, 255, 0), -1)
                                 
            # Puntos, ubicación, fuente, grosor, color, tamaño
            cv2.putText(frame, '{}, {}'.format(x, y), (x+10, y), font, 0.75, (0, 255, 0), 1, cv2.LINE_AA)
            cv2.drawContours(frame, [newContorno], 0, color, 3)

# Definimos el puerto de la cámara a emplear         
cap = cv2.VideoCapture(0)

font = cv2.FONT_HERSHEY_SIMPLEX
# Máscara de colores a detectar
Verde1= np.array([45,190,195], np.uint8)
Verde2= np.array([56,203,214], np.uint8)

Rojo1 = np.array([165,100,95], np.uint8)
Rojo2 = np.array([178,225,250], np.uint8)

# Mientras está activada la captura de video
while True:
    # Obtenemos un valor booleano e imagen
    ret, frame = cap.read()

    # Si hay imagen capturada
    if ret == True:

        # Pasamos de BGR a HSV
        frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        maskVerde=cv2.inRange(frameHSV, Verde1, Verde2)
        maskRojo=cv2.inRange(frameHSV, Rojo1, Rojo2)

        draw(maskRojo, (0, 0, 255))
        draw(maskVerde, (0,255,0))
      
        
        # Mostramos la ventana de captura
        cv2.imshow('Depresion', frame)
        
        # Detenemos la visualización con la tecla 's'
        if cv2.waitKey(1) & 0xFF == ord('s'):
            break

# Detenemos la captura de video
cap.release()
# Cerramos todas las ventanas
cv2.destroyAllWindows()