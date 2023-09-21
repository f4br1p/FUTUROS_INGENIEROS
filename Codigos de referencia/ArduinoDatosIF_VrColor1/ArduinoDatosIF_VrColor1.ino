
#include <Arduino.h>

// LIBRERIAS PARA EL SENSOR DE COLOR
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// ASIGNA UN NOMBRE AL SENSOR DE COLOR
SparkFun_APDS9960 apds;

// DEFINICION DE LA VARIABLE PARA LOS MENSAJES RECIBIDOS
char command;

/*
 CONEXIÓN DE PUENTE H - PLACA ARDUINO

 Parámetros ---- Nro de Pin en arduino
 * ENA-Pte H     6-Arduino
 * IN1-Pte H     7-Arduino
 * IN2-Pte H     8-Arduino
 * ENB-Pte H     11-Arduino
 * IN3-Pte H     9-Arduino
 * IN4-Pte H     10-Arduino
*/

// CONFIGURACIÓN DE PINES MOTOR IZQUIERDO
const int pinENA = 6; // Salida PWM para la potencia del motor
const int pinIN1 = 7;
const int pinIN2 = 8;

// CONFIGURACIÓN DE PINES MOTOR DERECHO
const int pinIN3 = 9;
const int pinIN4 = 10;
const int pinENB = 11; // Salida PWM para potencia del motor

// ARRAY PARA CARGAR VALORES DE LOS MOTORES
const int pinMotorDir[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorPot[3] = { pinENB, pinIN3, pinIN4 };


void setup() {

  Serial.begin(9600); //Definir comunicación serial
  apds.init(); // Inicializa el sensor de color
  apds.enableLightSensor(false); // Inhabilita la función de detectar de luz ambiental del sensor
  delay(500);

// DEFINIR PINES DE MOTOR IZQUIERDO COMO SALIDA
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

// DEFINIR PINES DE MOTOR DERECHO COMO SALIDA
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
}


void loop() {

  // Declara variables para guardar los valores detectados
  uint16_t red_light = 0;
  uint16_t green_light = 0;
  uint16_t blue_light = 0;


  // BUCLE IF GENERAL - Verifica si se pueden leer de los colores ROJO, AZUL y VERDE
  if (apds.readRedLight(red_light) &&
      apds.readGreenLight(green_light) &&
      apds.readBlueLight(blue_light)) { 
      // Si puede leerlos, imprime los valores de los colores con sus nombres:
    // Serial.print("Rojo: ");
    // Serial.print(red_light);
    // Serial.print(", Verde: ");
    // Serial.print(green_light);
    // Serial.print(", Azul: ");
    // Serial.println(blue_light);

    // PRIMER SUB BUCLE IF PARA LA DETECCIÓN DEL SENSOR DE COLOR
    if (red_light > blue_light && red_light > green_light && red_light > 40) {
      // Serial.println("Color detectado: Rojo");
      // DOBLA PARA SENTIDO **

    // SEGUNDO SUB BUCLE IF PARA DETECCIÓN DE COLOR
    } else if (blue_light > red_light && blue_light > green_light && blue_light > 60) {
      // Serial.println("Color detectado: Azul");
      // DOBLA PARA SENTIDO **

    // SI NO INGRESA A NINGUN SUB BUCLE
    } else {
      // Serial.println("Sigue buscando valores...");
    }

  // SI FALLA LA LECTURA DEL SENSOR DE COLOR
  } else {
    // Serial.println("Error al leer los valores de luz");
  }


  delay(1000); // Descanso del programa


  // BUCLE IF GENERAL PARA LOS DATOS RECIBIDOS DEL RASPBERRY PI
  if (Serial.available() > 0) { // Verifica si hay DATOS DISPONIBLES en el puerto serial
    command = Serial.read(); // Se lee el VALOR RECIBIDO y almacena en una variable "COMMAND"
    
    // Primer Sub-Bucle IF
    if (command == 'H') { // Se verifica si el DATO recibido es 'H', realiza lo siguiente:
      // Acciones
    } // Cierre del Primer Sub-Bucle IF

    // Segundo Sub-Bucle IF
    else if (command == 'L') { // Se verifica si el DATO recibido es 'L', realiza lo siguiente:
      // Acciones
    } // Cierre del Segundo Sub-Bucle IF

  } // Cierre del BUCLE IF GENERAL

  Serial.flush(); // LIMPIA EL PUERTO SERIAL DE DATOS RECIBIDOS
}


void RETROCEDER(){
// FUNCIÓN PARA RETROCEDER
}


void AVANZAR(){
// FUNCIÓN PARA AVANZAR 
}


void DERECHA(){
// FUNCIÓN PARA DIRECCIÓN DERECHA 
}


void IZQUIERDA(){
// FUNCIÓN PARA DIRECCIÓN IZQUIERDA
}


