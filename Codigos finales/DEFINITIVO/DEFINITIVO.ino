//definicion de pins
const int motorPin1 = 2;    // 28BYJ48 In1
const int motorPin2 = 3;    // 28BYJ48 In2
const int motorPin3 = 4;   // 28BYJ48 In3
const int motorPin4 = 5;   // 28BYJ48 In4

const int pinENA = 8;//salida PWM para la velocidad de motor
const int pinIN1 = 9;
const int pinIN2 = 10;

const int pinIN3 = 11;
const int pinIN4 = 12;
const int pinENB = 13;//salida PWM para la velocidad de motor 

const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };

const int waitTime = 2000;  //espera entre fases 20 seg
const int speed = 1;    //velocidad de giro

//definicion variables
int motorSpeed = 2400;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 400;  // pasos para una vuelta completa

const int sensorPin=8;

//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup()
{
  Serial.begin(9600);
  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(sensorPin, INPUT);

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);
  
}

void loop()
{
  moverDelante(pinMotorA, 135);
  moverDelante(pinMotorB, 135);
  int sensorValue = digitalRead(sensorPin);
  int numero = Serial.parseInt();
  if (numero == 1){
    for (int i = 0; i < stepsPerRev ; i++){
      clockwise();
      delayMicroseconds(motorSpeed);
    }
    delay(1000);
    numero=0;
    for (int i = 0; i < stepsPerRev ; i++){
      anticlockwise();
      delayMicroseconds(motorSpeed);
    }
  }else if (numero == 2){
    for (int i = 0; i < stepsPerRev ; i++){
      anticlockwise();
      delayMicroseconds(motorSpeed);
    }
    delay(1000);
    numero=0;
    for (int i = 0; i < stepsPerRev ; i++){
      clockwise();
      delayMicroseconds(motorSpeed);
    }
  }
}

void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}

void moverDelante(const int pinMotor[3], int speed)
{
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);
  //establece velocidad de motor
  analogWrite(pinMotor[0], speed);
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
