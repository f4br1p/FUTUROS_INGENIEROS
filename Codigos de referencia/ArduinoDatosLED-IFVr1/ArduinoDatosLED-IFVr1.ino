#include <arduino.h>

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
const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 }
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 }

//CONFIGURACIÓN DE LOS PINES LED
const int ledROJO = 13;
const int ledVERDE = 12;

void setup() {
  Serial.begin(9600); //Definir comunicación serial

// DEFINIR PINES DE MOTOR IZQUIERDO COMO SALIDA
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

// DEFINIR PINES DE MOTOR DERECHO COMO SALIDA
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

// CONFIGURACIÓN DE LOS LEDS COMO SALIDA
  pinMode(ledROJO, OUTPUT);
  pinMode(ledVERDE, OUTPUT);

}


void loop() {
// BUCLE IF GENERAL PARA LOS DATOS RECIBIDOS DEL RASPBERRY PI
  if (Serial.available() > 0) { // Verifica si hay DATOS DISPONIBLES en el puerto serial
    command = Serial.read(); // Se lee el VALOR RECIBIDO y almacena en una variable "COMMAND"
    
    // Primer Sub-Bucle IF
    if (command == 'H') { // Se verifica si el DATO recibido es 'H', realiza lo siguiente:
      // **DETECTÓ ROJO**
      digitalWrite(ledROJO, HIGH); // enciende ROJO
      // Acciones
      digitalWrite(ledROJO, LOW); // apaga ROJO
    } // Cierre del Primer Sub-Bucle IF

    // Segundo Sub-Bucle IF
    else if (command == 'L') { // Se verifica si el DATO recibido es 'L', realiza lo siguiente:
      // **DETECTÓ VERDE**
      digitalWrite(ledVERDE, HIGH); // enciende VERDE
      // Acciones
      digitalWrite(ledVERDE, LOW); // apaga VERDE
    } // Cierre del Segundo Sub-Bucle IF

  } // Cierre del BUCLE IF GENERAL
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


