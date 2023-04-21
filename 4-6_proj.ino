int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;

int rotateCount = 0;

enum state {
  startAir,
  noAir,
  wait,
  full
};

state currState;
state nextState;

void setup() {
  // put your setup code here, to run once:
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  currState = startAir;
  nextState = startAir;
}

void loop() {
  // put your main code here, to run repeatedly:
  currState = nextState;
  if (currState == startAir) {

  } else if (currState == noAir) {

  } else if (currState == wait) {

  } else {

  }
}

void motorNoAirFunc() {
  digitalWrite(directionPin, HIGH);
  digitalWrite(brakePin, LOW);
  analogWrite(pwmPin, 50);
  delay(200);
  digitalWrite(brakePin, HIGH);
  digitalWrite(pwmPin, 0);
  delay(5000);
}
