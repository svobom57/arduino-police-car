
#include <Servo.h>
#include <Moves.h>
#define TRIG_PIN 13
#define ECHO_PIN 12
#define BLUE_LED 11
#define RED_LED 10
#define M_RIGHT_SPEED 3
#define M_RIGHT_DIR 2
#define M_LEFT_SPEED 5
#define M_LEFT_DIR 4



const long servoInterval = 200;
unsigned long previousServoTime = 0;
bool fullyRotated = false;
double maxMeasuredDistance = 0;
int desiredPosition = 0;

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
  pinMode(M_RIGHT_SPEED,OUTPUT);
  pinMode(M_RIGHT_DIR,OUTPUT);
  pinMode(M_LEFT_SPEED,OUTPUT);
  pinMode(M_LEFT_DIR,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  goStraight();
  startMultiTasking();
}

void goStraight() {
  digitalWrite(M_RIGHT_DIR,HIGH);
  digitalWrite(M_LEFT_DIR,HIGH);
  analogWrite(M_RIGHT_SPEED,HIGH);
  analogWrite(M_LEFT_SPEED,HIGH);
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
  if (fullyRotated) {
      Serial.println("Moving...");
      Serial.println("Max Meaured Distance: ");
      Serial.println(maxMeasuredDistance);
      Serial.println("desiredPosition: ");
      Serial.print(desiredPosition);
      fullyRotated = false;
      maxMeasuredDistance = 0;
      desiredPosition = 0;
  }
}


void moveWithServo() {
  if (servoPosition > 180) {
    fullyRotated = true;
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
    Serial.print(distance);
    Serial.println(" cm");
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

