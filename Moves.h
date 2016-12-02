#define M_RIGHT_SPEED 3
#define M_RIGHT_DIR 2
#define M_LEFT_SPEED 5
#define M_LEFT_DIR 4
#define LOW_SPEED 125
#define MID_SPEED 130
#define HIGH_SPEED 150
#define MOVE_FRONT true
#define MOVE_BACK false
#define MOVE_LEFT true
#define MOVE_RIGHT false
#define IS_MOVING_LEFT 0
#define IS_MOVING_RIGHT 1

// Support

int getSpeedForDirection(bool direction, int speed){
  if(direction == MOVE_FRONT){
    return (255-speed+1);
  }
  return speed;
}

void setMotorsPolarityForDirection(int direction){
  if(direction){
    digitalWrite(M_RIGHT_DIR, HIGH);
    digitalWrite(M_LEFT_DIR, HIGH);
  }else{
    digitalWrite(M_RIGHT_DIR, LOW);
    digitalWrite(M_LEFT_DIR, LOW);
  }
}

// Moving

void goStraight(int speed) {
  setMotorsPolarityForDirection(MOVE_FRONT);
  analogWrite(M_RIGHT_SPEED, getSpeedForDirection(MOVE_FRONT, speed));
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(MOVE_FRONT, speed*1.5));
}

void goBackwards(int speed){
  setMotorsPolarityForDirection(MOVE_BACK);
  analogWrite(M_RIGHT_SPEED, getSpeedForDirection(MOVE_BACK, speed));
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(MOVE_BACK, speed*1.5));
}

void turnRight(bool direction){
  setMotorsPolarityForDirection(direction);
  analogWrite(M_RIGHT_SPEED, 0);
  analogWrite(M_LEFT_SPEED, 255);    
}

void turnLeft(bool direction){
  setMotorsPolarityForDirection(direction);
  analogWrite(M_RIGHT_SPEED, 255);
  analogWrite(M_LEFT_SPEED, 0);  
}


