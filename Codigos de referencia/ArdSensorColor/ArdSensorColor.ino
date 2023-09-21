
// DEFINE LIBRERIAS NECESARIAS PARA EL SENSOR DE COLOR
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// ASIGNA UN NOMBRE AL SENSOR DE COLOR
SparkFun_APDS9960 apds;

void setup() {
  Serial.begin(9600);
  apds.init(); // Inicializa el sensor de color
  apds.enableLightSensor(false); // Inhabilita la función de detectar de luz ambiental del sensor
  delay(500);
}

void loop() {
  // Declara variables para guardar los valores detectados
  uint16_t red_light = 0;
  uint16_t green_light = 0;
  uint16_t blue_light = 0;


  // IF GENERAL - Verifica si se pueden leer de los colores ROJO, AZUL y VERDE
  if (apds.readRedLight(red_light) &&
      apds.readGreenLight(green_light) &&
      apds.readBlueLight(blue_light)) { 
    // Si puede leerlos, imprime los valores de los colores con sus nombres:
    Serial.print("Rojo: ");
    Serial.print(red_light);
    Serial.print(", Verde: ");
    Serial.print(green_light);
    Serial.print(", Azul: ");
    Serial.println(blue_light);

    // SUB BUCLE IF - Verifica cual de los colores (AZUL O ROJO) es mayor para ver cúal acción se puede realizar
    if (red_light > blue_light && red_light > green_light && red_light > 40) { // Si ROJO es mayor y su valor supera el límite definido entra a la primera condición
      Serial.println("Color detectado: Rojo");
      // DOBLA PARA **

    } else if (blue_light > red_light && blue_light > green_light && blue_light > 60) { // Si AZUL es mayor y su valor supera el límite definido entra a la segunda condición
      Serial.println("Color detectado: Azul");
      // DOBLA PARA **
    } else { // Si no se cumple ninguna de las dos primeras condiciones, el coche seguirá avanzando
      Serial.println("Sigue avanzando");
    }
  } else {
    Serial.println("Error al leer los valores de luz"); // Si no funciona bien la lectura del sensor, se emite un mensaje de error
  }


  delay(1000);
}
