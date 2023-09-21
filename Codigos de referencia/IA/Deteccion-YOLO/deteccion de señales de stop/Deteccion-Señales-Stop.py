import torch
from pathlib import Path
from PIL import Image

# Cargar el modelo preentrenado con torch.hub
model = torch.hub.load('ultralytics/yolov5', 'yolov5s')

# Cargar la imagen de prueba desde la ruta local
ruta_imagen = "#"
im = Image.open(ruta_imagen)

# Realizar la detección en la imagen
results = model(im)

# Etiqueta de la señal de stop en YOLOv5
etiqueta_stop = 11

# Verificar si la señal de stop está presente en los resultados de la detección
if etiqueta_stop in results.pred[0][:, -1]:
    print("Los motores frenaron")
else:
    print("Continuamos sin frenar")
