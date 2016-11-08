
#include <Servo.h>
#define TRIG_PIN 13
#define ECHO_PIN 12
#define BLUE_LED 11
#define RED_LED 10

const long servoInterval = 200;
long previousServoTime = 0;

//Setting up servo
Servo servo;
int servoPosition = 0;
long duration = 0;
long distance = 0; 

void setup() {
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT); 
  servo.attach(9); // Attaching servo to 9 pin
}

void loop() {
  
//  for (servoPosition = 0; servoPosition <= 180; servoPosition += 20) { // moving with servo 
//    servo.write(servoPosition); // Moving with servo
//    distance = measureDistance();
//    signalizeDistance();
//    delay(500);  
//  }
  startMultiTasking();
}

void startMultiTasking() {
  unsigned long currentTime = millis();
  double maxMeasuredDistance = 0;
  int desiredPosition = servoPosition;
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
}


void moveWithServo() {
  if (servoPosition > 180) {
    servoPosition = 0;
  }
  servo.write(servoPosition); 
  if (servoPosition == 0) {
    delay(600);
  }
  servoPosition += 20;
}

void signalizeDistance() {
     if (distance < 20) {  // This is where the BLUE_LED On/Off happens
      digitalWrite(BLUE_LED,HIGH); // When the Red condition is met, the Green BLUE_LED should turn off
      digitalWrite(RED_LED,LOW);
    } else {
      digitalWrite(BLUE_LED,LOW);
      digitalWrite(RED_LED,HIGH);
    }
    if (distance >= 200 || distance <= 0){
      Serial.println("Out of range");
    } else {
      Serial.print(distance);
      Serial.println(" cm");
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

