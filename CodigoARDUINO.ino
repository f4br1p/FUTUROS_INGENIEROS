#include <Arduino.h>\

/*
 * CONEXIÓN DE PUENTE H Y PLACA ARDUINO
 * ...
 */

/*
 * Configuración pines motor izquierdo
 */
const int pinENA = 9;
const int pinIN1 = 5;
const int pinIN2 = 6;

/*
 * Configuración pines motor derecho
 */
const int pinIN3 = 7;
const int pinIN4 = 8;
const int pinENB = 10;

const int waitTime = 2000;
const int speed = 80;

//ARRAY de motores
const int pinMotorA[3] = {pinENA, pinIN1, pinIN2};
const int pinMotorB[3] = {pinENB, pinIN3, pinIN4};

int ledColor1 = 11;
int ledColor2 = 12;

char command;

//Configuracion para la limpieza de puerto Serial
int A=0;
int B=0;
unsigned long LastResetTimeA = 0;
unsigned long LastResetTimeB = 0;
const unsigned long ResetInterval = 5000;

//Configuracion del pin del sensor infrarrojo
const int sensorPin = 13;

void setup()
{  
  Serial.begin(9600);
  pinMode(ledColor1, OUTPUT);
  pinMode(ledColor2, OUTPUT);
  pinMode(pinIN1, OUTPUT);  //Motor A
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN3, OUTPUT);  //Motor B
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

  pinMode(sensorPin, INPUT);
}

void loop()
{
    int sensorValue = digitalRead(sensorPin);
  if (Serial.available() > 0){ // Si hay datos disponibles en el puerto serial
    command = Serial.read(); // Leer el comando recibido
    if (command == 'H'){ // Si el comando recibido es 'H' = Rojo Esquiva
      if (millis() - LastResetTimeA >= ResetInterval){
      A = 0;
      LastResetTimeA = millis();
      }
      digitalWrite(ledColor1, HIGH); //Enciende el LED

      detener(pinMotorA);
      detener(pinMotorB);
      delay(500);

      //Serial.println("muevo izq");
      //mueve a la IZQ 
      moverIZQ(pinMotorA,pinMotorB, 155);
      delay(300);

      //Serial.println("muevo adelante");
      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      delay(400);

      //Serial.println("muevo der");
      //mueve a la DER
      moverDER(pinMotorA,pinMotorB, 170);
      delay(300);

      //Serial.println("muevo adelante");
      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      //Serial.println("espero");
      delay(400);

      moverDER(pinMotorA, pinMotorB, 155);
      delay(300);

      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      delay(400);

      moverIZQ(pinMotorA, pinMotorB, 155);
      delay(300);

      digitalWrite(ledColor1, LOW); //Apaga el LED
    } else if (command == 'L'){ // Si el comando recibido es 'L' = Verde
      if (millis() - LastResetTimeB >= ResetInterval){
        B = 0;
        LastResetTimeB = millis();
      }
      digitalWrite(ledColor2, HIGH); //Enciende LED

      detener(pinMotorA);
      detener(pinMotorB);

      moverDER(pinMotorA, pinMotorB, 200);
      delay(2000);

      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      delay(400);

      moverIZQ(pinMotorA, pinMotorB, 155);
      delay(300);

      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      delay(400);

      moverIZQ(pinMotorA, pinMotorB, 200);
      delay(2000);

      moverDelante(pinMotorA, 200);
      moverDelante(pinMotorB, 200);
      delay(400);
      
      moverDER(pinMotorA, pinMotorB, 200);
      delay(2000);

      digitalWrite(ledColor2, LOW); //Apaga el LED
    }
  }
      //Segunda parte del IF principal abajo ***
  else if (sensorValue == LOW){
    detener(pinMotorA);
    detener(pinMotorB);

    moverDER(pinMotorA, pinMotorB, 170);
    delay(300);

    moverDelante(pinMotorA, 200);
    moverDelante(pinMotorB, 200);
    delay(200);
    //Serial.println("Obejto detectado");
  } else {
      //Tercera parte del IF principal abajo ***
    Serial.println("No se detecta nada");
    moverDelante(pinMotorA, 200);
    moverDelante(pinMotorB, 200);
  }
}

void moverDelante(const int pinMotor[3], int speed)
{
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
  //establece velocidad de motor
  analogWrite(pinMotor[0], speed);
}

void moverAtras(const int pinMotor[3], int speed)
{
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
  //establece velocidad de motor
  analogWrite(pinMotor[0], speed);
}

void moverIZQ(const int pinMotorA[3],const int pinMotorB[3], int speed)
{
  //motorA va hacia adelante
  digitalWrite(pinMotorA[1], HIGH);
  digitalWrite(pinMotorA[2], LOW);
  //establece velocidad de motor
  analogWrite(pinMotorA[0], speed);
  //motorB va hacia atrás
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], HIGH);
  //establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
  delay(900);
  //detiene motor A
  digitalWrite(pinMotorA[1],LOW);
  digitalWrite(pinMotorA[2],LOW);
  analogWrite(pinMotorA[0],0);
  //detiene motor B
  digitalWrite(pinMotorB[1],LOW);
  digitalWrite(pinMotorB[2],LOW);
  analogWrite(pinMotorB[0],0);
}

void moverDER(const int pinMotorA[3], const int pinMotorB[3], int speed)
{
  // motorA va hacia atrás
  digitalWrite(pinMotorA[1], LOW);
  digitalWrite(pinMotorA[2], HIGH);
  // establece velocidad de motor
  analogWrite(pinMotorA[0], speed);
  // motorB va hacia adelante
  digitalWrite(pinMotorB[1], HIGH);
  digitalWrite(pinMotorB[2], LOW);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
  delay(1000);
  //detiene motor A
  digitalWrite(pinMotorA[1],LOW);
  digitalWrite(pinMotorA[2],LOW);
  analogWrite(pinMotorA[0],0);
  //detiene motor B
  digitalWrite(pinMotorB[1],LOW);
  digitalWrite(pinMotorB[2],LOW);
  analogWrite(pinMotorB[0],0);
}

void detener(const int pinMotor[3])
{
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);
  //establece velocidad motor 
  analogWrite(pinMotor[0], 0);
}

