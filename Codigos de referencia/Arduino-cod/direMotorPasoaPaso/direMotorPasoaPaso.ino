//definicion de pins
const int motorPin1 = 2;    // 28BYJ48 In1
const int motorPin2 = 3;    // 28BYJ48 In2
const int motorPin3 = 4;   // 28BYJ48 In3
const int motorPin4 = 5;   // 28BYJ48 In4

//definicion variables
int motorSpeed = 2400;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 400;  // pasos para una vuelta completa

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
}

void loop()
{
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
