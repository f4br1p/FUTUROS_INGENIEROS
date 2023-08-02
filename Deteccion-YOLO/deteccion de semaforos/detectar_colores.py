import cv2

# Definir los rangos de color para rojo y verde en el espacio HSV
lower_red = (0, 120, 70)
upper_red = (10, 255, 255)
lower_green = (40, 40, 40)
upper_green = (80, 255, 255)

def detectar_colores(image):
    # Convertir el frame de BGR a RGB para usarlo en la detección de colores
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Convertir el frame de RGB a HSV
    hsv = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2HSV)

    # Crear máscaras para el color rojo y verde
    mask_red = cv2.inRange(hsv, lower_red, upper_red)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    # Encontrar los contornos en la máscara del color rojo y verde
    contours_red, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_green, _ = cv2.findContours(mask_green, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Verificar si se detectó el color rojo y realizar la acción correspondiente
    if len(contours_red) > 0:
        print("¡Detenerse! Se detectó el color rojo.")
        return "rojo"
    elif len(contours_green) > 0:
        print("¡Adelante! Se detectó el color verde.")
        return "verde"
    else:
        print("No se detectó ningún color relevante.")
        return None
