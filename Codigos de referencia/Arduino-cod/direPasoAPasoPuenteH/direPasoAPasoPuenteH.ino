//definicion de pins
const int motorPin1 = 2;    // 28BYJ48 In1
const int motorPin2 = 3;    // 28BYJ48 In2
const int motorPin3 = 4;   // 28BYJ48 In3
const int motorPin4 = 5;   // 28BYJ48 In4

int Blue =0;
int Green =0;
int Contador = 0;
int B=0;
int c=0;
int G=100;

const int pinENA = 8; // Salida PWM para la potencia del motor
const int pinIN1 = 9;
const int pinIN2 = 10;

// CONFIGURACIÓN DE PINES MOTOR DERECHO
const int pinIN3 = 11;
const int pinIN4 = 12;
const int pinENB = 13; // Salida PWM para potencia del motor


//definicion variables
int motorSpeed = 2400;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 400;  // pasos para una vuelta completa

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
}

void loop()
{
  AVANZAR(pinMotorA, 135);
  AVANZAR(pinMotorB, 135);
  B=1;
  c=2;
  for (int a =1; a >= G; a++){
    if (Contador <= 12){
      if ( a == B){
        for (int i = 0; i < stepsPerRev ; i++){
          clockwise();
          delayMicroseconds(motorSpeed);
        }
        delay(1000);
        for (int i = 0; i < stepsPerRev ; i++){
          anticlockwise();
          delayMicroseconds(motorSpeed);
        }
        Contador= Contador+1;
        B=B+2;
      }else if (a == c){
        for (int i = 0; i < stepsPerRev ; i++){
          anticlockwise();
          delayMicroseconds(motorSpeed);
        }
        delay(1000);
        for (int i = 0; i < stepsPerRev ; i++){
          clockwise();
          delayMicroseconds(motorSpeed);
        }
        Contador= Contador+1;
        c= c+2;
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
void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
