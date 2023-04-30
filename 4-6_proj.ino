/******************************************INCOMPLETE**********************************************
    
    Motor Control Main

    Uses a finite state machine (FSM) to control a motor and an LED based on the input from a mass
    air flow sensor (MAF). The input from the MAF is converted to a 10-bit unsigned integer.
    The starting state will transition to the noAir state when the sensor doesn't detect air,
    turning the motor by 60 degrees, then transition back to the initial state. After turning the
    motor 6 times, noAir will instead transition to the full state, turning on an LED, and remain 
    there. Each state is separated by 1 second, except for noAir, which is separated by 5.

    Inputs:
      * mafPin       : analog   //signal from the MAF determining mass air flow      

    Outputs:
      * directionPin : digital  //controls the motor direction
      * brakePin     : digital  //makes the motor stop faster
      * ledPin       : digital  //controls the LED
      * pwmPin       : analog   //controls the motor using PWM

    Created 04-06-2023
    Kamila Errigo
    Modified 04-26-2023
    Kamila Errigo

    https://github.com/k-errigo/filter-control-arduino

**************************************************************************************************/

//pins
int directionPin = 12;
int pwmPin = A3;
int brakePin = 9;
int ledPin = 13;
int mafPin = A2

//keeps track of the number of times air isn't sensed
int count = 0;

//analog value converted to discrete int value of range 0-1023
int sensorValue = 0;

//state types
enum state {
  startAir,
  noAir,
  full
};

//keep track of states
state currState;
state nextState;

// setup()
// Sets up pins and initializes output values (preventing undefined behavior)
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void setup() {
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(mafPin, INPUT);

  digitalWrite(directionPin, HIGH);
  digitalWrite(brakePin, HIGH);
  analogWrite(pwmPin, 0);
  digitalWrite(ledPin, LOW);

  currState = startAir;
  nextState = startAir;
}

// loop()
// Next state logic, runs continuously. Updates the next state once every second.
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void loop() {
  
  //update current state and sensor value
  currState = nextState;
  sensorValue = analogRead(mafPin);

  //current state output logic and next state logic, don't see a need to separate them
  if (currState == startAir) {
    digitalWrite(brakePin, HIGH);
    analogWrite(pwmPin, 0);

    (sensorValue <= 102) ? (nextState = noAir) : (nextState = startAir);
  } else if (currState == noAir) {
    motorNoAirFunc();
    count++;
    
    (count == 6) ? (nextState = full) : (nextState = startAir);
  } else {
    fullFilter();
    
    nextState = full;
  }
  delay(1000);
}

// motorNoAirFunc()
// Describes the output logic for the noAir state
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void motorNoAirFunc() {
  digitalWrite(directionPin, HIGH);   //should always stay the same direction
  digitalWrite(brakePin, LOW);

  //intended to turn 60 degrees, may not be accurate values
  analogWrite(pwmPin, 50);
  delay(200);

  //turn off and delay for 4 seconds, 5th second in state logic
  digitalWrite(brakePin, HIGH);
  digitalWrite(pwmPin, 0);
  delay(4000);
}

// fullFilter()
// Describes the output logic for the full state
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void fullFilter() {
  digitalWrite(brakePin, HIGH);
  analogWrite(pwmPin, 0);
  digitalWrite(ledPin, HIGH);
}


// Lani Lin-Kissick's compilation of K. Errigo's motor code and Lani's MAF code is below.

/**Title: Jr23LPQ Arduino 2 Recieve MAF Sensor Info + (Work Motor)
 *Author: Lani Lin-Kissick of Jr23LPQ's GS@IP Innovations Team II
*Date: 18Apr23, 27Apr23, 30Apr23
*Version: v1.0
*Purpose: Learning how to write Arduino program to understand, recieve, and interpret sensor information. 
Arduino needs to use information to tell the motor to rotate 60º --> rotating the filter medium.
 &
****Motor Control Main**: Paul's sister's code, edited by Lani Lin-Kissick 27Apr23, 30Apr23

    Uses a finite state machine (FSM) to control a motor and an LED based on the input from a mass
    air flow sensor (MAF). The input from the MAF is converted to a 10-bit unsigned integer.
    The starting state will transition to the noAir state when the sensor doesn't detect air,
    turning the motor by 60 degrees, then transition back to the initial state. After turning the
    motor 6 times, noAir will instead transition to the full state, turning on an LED, and remain 
    there. Each state is separated by 1 second, except for noAir, which is separated by 5.

    Inputs:
      * mafPin       : analog   //signal from the MAF determining mass air flow      

    Outputs:
      * directionPin : digital  //controls the motor direction
      * brakePin     : digital  //makes the motor stop faster
      * ledPin       : digital  //controls the LED
      * pwmPin       : analog   //controls the motor using PWM

    Created 04-06-2023
    Kamila Errigo
    Modified 04-26-2023
    Kamila Errigo

    https://github.com/k-errigo/filter-control-arduino
*********
**/int ldr = A0; //ldr stands for light dependent resistor which I don't know its affiliation with this MAF sensor
// analogRead, which is what I want Arduino Uno to do: read the analog MAF sensor information
// lines 12-50 are motor setup
//pins
int directionPin = 12;
int pwmPin = A3;
int brakePin = 9;
int ledPin = 13; //on the board, it's currently on diff pins
int mafPin = A2;

//keeps track of the number of times air isn't sensed
int count = 0;

//analog value converted to discrete int value of range 0-1023
int sensorValue = 0;

//state types
enum state {
  startAir,
  noAir,
  full
};

//keep track of states
state currState;
state nextState;

// setup()
// Sets up pins and initializes output values (preventing undefined behavior)
//   Inputs:
//     N/A
//   Outputs:
//     N/A


// loop()
// Next state logic, runs continuously. Updates the next state once every second.
//   Inputs:
//     N/A
//   Outputs:
//     N/A

void setup() {
  // put your setup code here, to run once:
  pinMode(ldr, INPUT); //initialize ldr as INPUT
  Serial.begin(9600); //begin the serial monitor at 9600 baud

  //motor setup below

  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(mafPin, INPUT);

  digitalWrite(directionPin, HIGH);
  digitalWrite(brakePin, HIGH);
  analogWrite(pwmPin, 0);
  digitalWrite(ledPin, LOW);

  currState = startAir;
  nextState = startAir;
}

void loop() {
  // put your main code here, to run repeatedly:
  int voltage=analogRead(ldr);
  Serial.print("ldr reading=");
  Serial.println(voltage);
  delay(1000); // stated as last loop line as well

  // motor loop code

  //update current state!!!
  currState = nextState;
  sensorValue = analogRead(mafPin);

  //current state output logic and next state logic, don't see a need to separate them
  if (currState == startAir) {
    digitalWrite(brakePin, HIGH);
    analogWrite(pwmPin, 0);

    (sensorValue <= 102) ? (nextState = noAir) : (nextState = startAir);
  } else if (currState == noAir) {
    void motorNoAirFunc();
    count++;
    
    (count == 6) ? (nextState = full) : (nextState = startAir);
  } else {
    fullFilter();
    
    nextState = full;
  }
  delay(1000);
}

// motorNoAirFunc()
// Describes the output logic for the noAir state
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void motorNoAirFunc() {
  digitalWrite(directionPin, HIGH);   //should always stay the same direction
  digitalWrite(brakePin, LOW);

  //intended to turn 60 degrees, may not be accurate values
  analogWrite(pwmPin, 50);
  delay(200);

  //turn off and delay for 4 seconds, 5th second in state logic
  digitalWrite(brakePin, HIGH);
  digitalWrite(pwmPin, 0);
  delay(4000);
}

// fullFilter()
// Describes the output logic for the full state
//   Inputs:
//     N/A
//   Outputs:
//     N/A
void fullFilter() {
  digitalWrite(brakePin, HIGH);
  analogWrite(pwmPin, 0);
  digitalWrite(ledPin, HIGH);
}
