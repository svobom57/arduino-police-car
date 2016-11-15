void goStraight(int speed) {
  digitalWrite(M_RIGHT_DIR,HIGH);
  digitalWrite(M_LEFT_DIR,HIGH);
  analogWrite(M_RIGHT_SPEED,speed);
  analogWrite(M_LEFT_SPEED,speed);
}

void goBackwards(int speed){
  digitalWrite(M_RIGHT_DIR,LOW);
  digitalWrite(M_LEFT_DIR,LOW);
  analogWrite(M_RIGHT_SPEED,speed);
  analogWrite(M_LEFT_SPEED,speed);
}
