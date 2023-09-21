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
int A=0;
// ARRAY PARA CARGAR VALORES DE LOS MOTORES
const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };

const int speed = 100;    //velocidad de giro

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
}


void loop() {
  Serial.println("Muevo 'IZQ'");
  IZQUIERDA(pinMotorA, 145);

  delay(80);
  APAGAR(pinMotorA, 135);
  delay(1000);

  Serial.println("Muevo 'DER'");
  DERECHA(pinMotorA, 135);

  delay(100);

  APAGAR(pinMotorA, 135);
  delay(1000);
}


void RETROCEDER(const int pinMotorB[3], int speed){
// FUNCIÓN PARA RETROCEDER


  // motorB va hacia adelante
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], HIGH);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
  
  delay(100);

  // detiene motor B
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], LOW);
  analogWrite(pinMotorB[0], 0);
}
void APAGAR(const int pinMotorB[3], int speed){
// FUNCIÓN PARA RETROCEDER


  // motorB va hacia adelante
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], LOW);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);
  
  delay(100);
}

void AVANZAR(const int pinMotorB[3], int speed){
// FUNCIÓN PARA AVANZAR 

  // motorB va hacia adelante
  digitalWrite(pinMotorB[1], HIGH);
  digitalWrite(pinMotorB[2], LOW);
  // establece velocidad de motor
  analogWrite(pinMotorB[0], speed);

  delay(100);

  // detiene motor B
  digitalWrite(pinMotorB[1], LOW);
  digitalWrite(pinMotorB[2], LOW);
  analogWrite(pinMotorB[0], 0);
}


void DERECHA(const int pinMotorA[3], int speed){
// FUNCIÓN PARA DIRECCIÓN DERECHA 

  //motorA dirección va hacia un lado
  digitalWrite(pinMotorA[1], LOW);
  digitalWrite(pinMotorA[2], HIGH);
  //establece velocidad de motor
  analogWrite(pinMotorA[0], speed);

  delay(80);
}


void IZQUIERDA(const int pinMotorA[3], int speed){
// FUNCIÓN PARA DIRECCIÓN IZQUIERDA

  //motorA dirección va hacia un lado
  digitalWrite(pinMotorA[1], HIGH);
  digitalWrite(pinMotorA[2], LOW);
  //establece velocidad de motor
  analogWrite(pinMotorA[0], speed);

  delay(100);
}


