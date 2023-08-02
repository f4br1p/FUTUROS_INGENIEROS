import cv2
import torch
from models.experimental import attempt_load

# Ruta al archivo de pesos del modelo previamente entrenado para detectar semáforos con YOLOv5
weights_path = "#"

# Cargar el modelo YOLOv5
model = attempt_load(weights_path, map_location=torch.device('cpu'))

def detectar_semaforos(image_path):
    # Cargar la imagen
    image = cv2.imread(image_path)

    # Procesar la imagen con YOLOv5
    results = model(image)

    # Obtener las coordenadas de las detecciones y las etiquetas de las clases
    predictions = results.pandas().xyxy[0]

    # Filtrar las detecciones para obtener solo el semáforo
    semaphore_predictions = predictions[predictions["name"] == "semaphore"]

    # Verificar si se detectó un semáforo
    if not semaphore_predictions.empty:
        print("Se detectó un semáforo.")
        return True
    else:
        print("No se detectó un semáforo.")
        return False
