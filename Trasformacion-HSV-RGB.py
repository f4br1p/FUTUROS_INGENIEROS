# Empezamos incluyendo las librerías a emplear
import cv2
import numpy as np
# Definimos las variables donde se alojará el valor RGB y la transformación.
rgb_value= np.uint8([[[238,39,55]]])
hsv_value=cv2.cvtColor(rgb_value, cv2.COLOR_RGB2HSV)
#Extraemos individualmente cada valor HSV
hue=hsv_value[0,0,0]
saturation=hsv_value[0,0,1]
value= hsv_value[0,0,2]
#Imprimimos por serial los valores
print(f"Valor RGB")
print(f"V:=[{hue},{saturation},{value}]")