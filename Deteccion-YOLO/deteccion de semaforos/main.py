from detectar_semaforos import detectar_semaforos
from detectar_colores import detectar_colores

# Ruta de la imagen que deseas detectar (reemplaza por la ruta de tu imagen)
image_path = "#"

# Detectar si hay un semáforo en la imagen
if detectar_semaforos(image_path):
    print("Se detectó un semáforo. Activando la detección de colores.")
    resultado_deteccion_colores = detectar_colores(image_path)
    if resultado_deteccion_colores == "rojo":
        # Realizar la acción de detener el movimiento de tu vehículo o robot.
        print("Deteniendo el vehículo o robot.")
    elif resultado_deteccion_colores == "verde":
        #Realizar la acción de avanzar con tu vehículo o robot.
        print("Avanzando con el vehículo o robot.")
    else:
        print("No se detectó ningún color relevante.")
else:
    print("No se detectó un semáforo.")
