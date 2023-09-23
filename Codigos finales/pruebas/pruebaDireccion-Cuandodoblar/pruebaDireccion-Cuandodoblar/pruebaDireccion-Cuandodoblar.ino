#include <Arduino.h>

// LIBRERIAS PARA EL SENSOR DE COLOR
#include <Wire.h>
#include <SparkFun_APDS9960.h>
SparkFun_APDS9960 apds;
char command;
int vueltas =0;

//Variables confirmación de dirección
int dire =0;
int sentido1=0;
int sentido2=0;

//definicion de pins
const int motorPin1 = 2;    // 28BYJ48 In1
const int motorPin2 = 3;    // 28BYJ48 In2
const int motorPin3 = 4;   // 28BYJ48 In3
const int motorPin4 = 5;   // 28BYJ48 In4

//definicion variables
int motorSpeed = 2400;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 400;  // pasos para una vuelta completa


const int pinENA = 8; // Salida PWM para la potencia del motor
const int pinIN1 = 9;
const int pinIN2 = 10;

// CONFIGURACIÓN DE PINES MOTOR DERECHO
const int pinIN3 = 11;
const int pinIN4 = 12;
const int pinENB = 13; // Salida PWM para potencia del motor

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };
const int speed = 100;    //velocidad de giro

void setup()
{
  Serial.begin(9600);
  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // DEFINIR PINES DE MOTOR IZQUIERDO COMO SALIDA
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

// DEFINIR PINES DE MOTOR DERECHO COMO SALIDA
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  apds.init();// Inicializa el sensor de color
  apds.enableLightSensor(false); // Inhabilita la función de detectar de luz ambiental del sensor
  delay(500);
}

void loop()
{
  // Declara variables para guardar los valores detectados
  uint16_t red_light = 0;
  uint16_t green_light = 0;
  uint16_t blue_light = 0;

  AVANZAR(pinMotorA, 135);
  AVANZAR(pinMotorB, 135);

  if (vueltas != 12){
    if (apds.readRedLight(red_light) && apds.readGreenLight(green_light) && apds.readBlueLight(blue_light)){
      if (Sentido1==0){
        if(red_light > blue_light && red_light > green_light && red_light > 40){
          //Color rojo, dirección izq HORARIO
          for (int i = 0; i < stepsPerRev ; i++){
            clockwise();
            delayMicroseconds(motorSpeed);
          }
          delay(25);
          for (int i = 0; i < stepsPerRev ; i++){
            anticlockwise();
            delayMicroseconds(motorSpeed);
          }
          vueltas = vueltas +1
          Sentido2 = 1;
        }
      }else if (Sentido2==0){
        if(blue_light > red_light && blue_light > green_light && blue_light > 60){
          //Color Azul, dirección dr ANTIHORARIO
          for (int i = 0; i < stepsPerRev ; i++){
            anticlockwise();
            delayMicroseconds(motorSpeed);
          }
          delay(25);
          for (int i = 0; i < stepsPerRev ; i++){
            clockwise();
            delayMicroseconds(motorSpeed);
          }
          vueltas = vueltas +1
          Sentido1 =1;
        }
      }  
    } else {
      Serial.println("ERROR");
    }
}
void AVANZAR(const int pinMotorB[3], int speed){
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], HIGH);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
}
void clockwise(){
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
void anticlockwise(){
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
void setOutput(int step){
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
