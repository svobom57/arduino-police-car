// Support

int getSpeedForDirection(bool direction, int speed){
  if(direction == MOVE_FRONT){
    return (255-speed)*-1;
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
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(MOVE_FRONT, speed));
}

void goBackwards(int speed){
  setMotorsPolarityForDirection(MOVE_BACK);
  analogWrite(M_RIGHT_SPEED, getSpeedForDirection(MOVE_BACK, speed));
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(MOVE_BACK, speed));
}

void turnRight(bool direction){
  setMotorsPolarityForDirection(direction);
  analogWrite(M_RIGHT_SPEED, getSpeedForDirection(direction, MID_SPEED));
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(direction, HIGH_SPEED));
  
}

void turnLeft(bool direction){
  setMotorsPolarityForDirection(direction);
  analogWrite(M_RIGHT_SPEED, getSpeedForDirection(direction, HIGH_SPEED));
  analogWrite(M_LEFT_SPEED, getSpeedForDirection(direction, MID_SPEED));
  
}


