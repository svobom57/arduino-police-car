
#include "Config.h"
#include <Servo.h>
#include "Moves.h"

const long servoInterval = 40; // 40
const long moveInterval = 300;
unsigned long previousServoTime = 0;
unsigned long previousMoveTime = 0;
double maxMeasuredDistance = 0;
double minMeasuredDistance = 100000;
int desiredPosition = 0;
int undesiredPosition = 0;
int servoDirection = MOVE_RIGHT;
double distances[3];

//Setting up servo
Servo servo;
int servoPosition = 0;
long duration = 0;
int distance = 0; 

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT); 
  servo.attach(9); // Attaching servo to 9 pin
  pinMode(M_RIGHT_SPEED,OUTPUT);
  pinMode(M_RIGHT_DIR,OUTPUT);
  pinMode(M_LEFT_SPEED,OUTPUT);
  pinMode(M_LEFT_DIR,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  startMultiTasking();
}

void startMultiTasking() {
  unsigned long currentTime = millis();
  //Move with servo
  if (currentTime - previousServoTime >= servoInterval) {
    previousServoTime = currentTime;
    scanSurroundings();
  }
  if (currentTime - previousMoveTime >= moveInterval) {
    previousMoveTime = currentTime;
    moveWithCar();
  }
}

void scanSurroundings() {
  moveWithServo(); 
  distances[0] = measureDistance();
  distances[1] = measureDistance();
  distances[2] = measureDistance();
  sort(distances, 3);
  // Median
  distance = distances[1];
  if (distance > maxMeasuredDistance) {
    maxMeasuredDistance = distance;
    desiredPosition = servoPosition;
  }
  if (distance < minMeasuredDistance){
    minMeasuredDistance = distance;
    undesiredPosition = servoPosition;
  }
  signalizeDistance();
}

void moveWithCar() {
  if(minMeasuredDistance >= 45){
      goStraight(HIGH_SPEED);    
  } else if(minMeasuredDistance <= 20){
    if (undesiredPosition <= 90) {
      turnLeft(MOVE_BACK);
    } 
    if (desiredPosition >= 91) {
      turnRight(MOVE_BACK);
    }
  }
  else{
    if (desiredPosition > 70 && desiredPosition < 110) {
      goStraight(MID_SPEED);
    }
    if (desiredPosition <= 70) {
      turnLeft(MOVE_FRONT);
    } 
    if (desiredPosition >= 110) {
      turnRight(MOVE_FRONT);
    }
  }
  minMeasuredDistance = 100000;
  maxMeasuredDistance = 0;
}

void moveWithServo() {
  servo.write(servoPosition); 
  if (servoPosition >= 140) {
    servoDirection = MOVE_LEFT;
  } 
  if (servoPosition <= 20) {
    servoDirection = MOVE_RIGHT;
  }
  if (servoDirection == MOVE_LEFT) {
    servoPosition -= 20;
  } else {
    servoPosition += 20;
  }
}

void signalizeDistance() {
     if (distance < 20) {  // This is where the BLUE_LED On/Off happens
      digitalWrite(BLUE_LED,HIGH); // When the Red condition is met, the Green BLUE_LED should turn off
      digitalWrite(RED_LED,LOW);
    } else {
      digitalWrite(BLUE_LED,LOW);
      digitalWrite(RED_LED,HIGH);
    }
}

double measureDistance() {
    digitalWrite(TRIG_PIN, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    return (duration/2) / 29.1; // returns distance
}

void sort(double a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

// Debug

void printStatus() {
    Serial.println("---------------");
    Serial.print("Max measured distance: ");
    Serial.println(maxMeasuredDistance);
    Serial.print("Desired position: ");
    Serial.println(desiredPosition);
    Serial.print("Min measured distance: ");
    Serial.println(minMeasuredDistance);
    Serial.print("Undesired position: ");
    Serial.println(undesiredPosition);
    Serial.println("---------------");
}


