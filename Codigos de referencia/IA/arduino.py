import serial
import time
import cv2

# Configurar la conexión serial con el Arduino
arduino_port = '/dev/ttyACM0'  # Ajustar el puerto del Arduino según corresponda
arduino_baudrate = 9600
arduino = serial.Serial(arduino_port, arduino_baudrate)

# Definir los rangos de color para el rojo en el espacio HSV
lower_red = (0, 120, 70)
upper_red = (10, 255, 255)

# Inicializar la cámara del Raspberry Pi
cap = cv2.VideoCapture(0)  # Usar 0 para la cámara predeterminada

try:
    while True:
        # Capturar el frame de la cámara
        ret, frame = cap.read()
        if not ret:
            break

        # Convertir el frame de BGR a HSV
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Crear una máscara para el color rojo
        mask_red = cv2.inRange(hsv, lower_red, upper_red)

        # Contar los píxeles rojos en la máscara
        count_red_pixels = cv2.countNonZero(mask_red)

        # Verificar si se detectó el color rojo
        if count_red_pixels > 100:  # Ajustar el valor según sea necesario
            print("Se detectó un color rojo. Frenando los motores.")
            # Enviar la señal al Arduino para detener los motores
            arduino.write(b'STOP\n')
        else:
            print("No se detectó un color rojo.")

        # Mostrar el frame con la detección en una ventana
        cv2.imshow("Detected Red", mask_red)

        # Salir del bucle si se presiona la tecla 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    # Cerrar la conexión serial y liberar la cámara
    arduino.close()
    cap.release()
    cv2.destroyAllWindows()
