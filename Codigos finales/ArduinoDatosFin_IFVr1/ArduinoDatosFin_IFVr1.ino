#include <Arduino.h>

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
const int pinENA = 8; // Salida PWM para la potencia del motor
const int pinIN1 = 9;
const int pinIN2 = 10;

// CONFIGURACIÓN DE PINES MOTOR DERECHO
const int pinIN3 = 11;
const int pinIN4 = 12;
const int pinENB = 13; // Salida PWM para potencia del motor

// ARRAY PARA CARGAR VALORES DE LOS MOTORES
const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };
const int speed = 100;    //velocidad de giro


// VARIABLES DE STEP-MOTOR
int motorSpeed = 2400;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 350;  // pasos para una vuelta completa

// DEFINICION DE PINES STEP-MOTOR
const int motorPin1 = 3;    // 28BYJ48 In1
const int motorPin2 = 4;    // 28BYJ48 In2
const int motorPin3 = 5;   // 28BYJ48 In3
const int motorPin4 = 6;   // 28BYJ48 In4

//Definicion puerto sensor infrarojo
const int SensorPin=2;

// SECUENCIA MEDIA FASE
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

// VARIABLES DE CONFIRMACION DE DIRECCION
int dire =0;
int Sentido1=0;
int Sentido2=0;

int vueltas =0; // Definicion de vueltas 
int sentido1=0; //sentido de la pista
int sentido2=0;

char command; // Definicion de comando raspy


void setup() {
  Serial.begin(9600); //Definir comunicación serial

  // DECLARAR PINES DEL STEP-MOTOR COMO SALIDA
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // DEFINIR PINES DE MOTOR DC IZQUIERDO COMO SALIDA
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

  // DEFINIR PINES DE MOTOR DC DERECHO COMO SALIDA
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  pinMode(SensorPin, INPUT);

}


void loop() {
  AVANZAR(pinMotorA, 135);
  AVANZAR(pinMotorB, 135);
  int sensorValue = digitalRead(SensorPin);
  // BUCLE IF GENERAL PARA LOS DATOS RECIBIDOS DEL RASPBERRY PI
  if (vueltas != 12){
    if (Serial.available() > 0) { // Verifica si hay DATOS DISPONIBLES en el puerto serial
      command = Serial.read(); // Se lee el VALOR RECIBIDO y almacena en una variable "COMMAND"
      // Primer Sub-Bucle IF
      if (sentido1==0){
        if (command == 'H') { // Se verifica si el DATO recibido es 'H', realiza lo siguiente:
          // **DETECTÓ ROJO**
          for (int i = 0; i < stepsPerRev ; i++){
          clockwise();
          delayMicroseconds(motorSpeed);
          }
          delay(25);
          for (int i = 0; i < stepsPerRev ; i++){
          anticlockwise();
          delayMicroseconds(motorSpeed);
          }
        } // Cierre del Primer Sub-Bucle IF
        vueltas = vueltas +1;
        sentido2=1;
      } 
      // Segundo Sub-Bucle IF
      else if (sentido2==0){
        if (command == 'L') { // Se verifica si el DATO recibido es 'L', realiza lo siguiente:
          // **DETECTÓ VERDE**
          for (int i = 0; i < stepsPerRev ; i++){
          anticlockwise();
          delayMicroseconds(motorSpeed);
          }
          delay(25);
          for (int i = 0; i < stepsPerRev ; i++){
          clockwise();
          delayMicroseconds(motorSpeed);
          }
        } // Cierre del Segundo Sub-Bucle IF
        vueltas = vueltas +1;
        sentido1=1;
      }// Cierre del BUCLE IF GENERAL
    Serial.flush(); // LIMPIA EL PUERTO SERIAL DE DATOS RECIBIDOS
    }else if (sensorValue == LOW){
      ATRAS(pinMotorA, 135);
      ATRAS(pinMotorB, 135);
      delay(50);
      for (int i = 0; i < stepsPerRev ; i++){
      clockwise();
      delayMicroseconds(motorSpeed);
      }
      delay(25);
      for (int i = 0; i < stepsPerRev ; i++){
      anticlockwise();
      delayMicroseconds(motorSpeed);
      }
    }
  }
}
void AVANZAR(const int pinMotorB[3], int speed){
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], HIGH);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
}

void ATRAS(const int pinMotorB[3], int speed){
  digitalWrite(pinMotorB[1], HIGH);
  digitalWrite(pinMotorB[2], LOW);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
}

void setOutput(int step){
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}

// FUNCIÓN SENTIDO HORARIO
void clockwise(){
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}

// FUNCIÓN SENTIDO ANTI-HORARIO
void anticlockwise(){
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}




