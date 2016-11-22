
#include "Config.h"
#include <Servo.h>
#include "Moves.h"

const long servoInterval = 100;
const long moveInterval = 1500;
unsigned long previousServoTime = 0;
unsigned long previousMoveTime = 0;
double maxMeasuredDistance = 0;
int desiredPosition = 0;
int servoDirection = MOVE_RIGHT;

//Setting up servo
Servo servo;
int servoPosition = 0;
long duration = 0;
long distance = 0; 

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
      moveWithServo(); 
      distance = measureDistance(); 
      if (distance > maxMeasuredDistance) {
        maxMeasuredDistance = distance;
        desiredPosition = servoPosition;
      }
      signalizeDistance();
  }
  if (currentTime - previousMoveTime >= moveInterval) {
    previousMoveTime = currentTime;
    Serial.print("Max measured distance: ");
    Serial.println(maxMeasuredDistance);
    Serial.print("Desired position: ");
    Serial.println(desiredPosition);
    if (random(2) == 0) {
      Serial.print("Going straigth");
      goStraight(HIGH_SPEED);
    } else {
      Serial.print("Going backwards");
      goBackwards(MID_SPEED);
    }
    maxMeasuredDistance = 0;
  }
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

