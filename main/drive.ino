void drive_in_current_direction(){
  switch (current_drive_status) {
    case D_FORWARD: drive_idle(); drive_in_direction(robot_direction); break;
    case D_BACKWARD: drive_idle(); drive_backward(); break;
    case D_LEFT: drive_idle(); drive_left(robot_direction); break;
    case D_RIGHT: drive_idle(); drive_right(robot_direction); break;
    case D_SPIN_LEFT: drive_idle(); spin_left(); break;
    case D_SPIN_RIGHT: drive_idle(); spin_right(); break;
    case D_IDLE: drive_idle(); break;
    default: break;
  }
}

void drive_in_direction(byte d){
  drive_right(d);
  drive_left(d);
}

void drive_right(byte d){
  digitalWrite(motor2_A, (d + 1) % 2); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, d % 2);
  analogWrite(motor2_Speed, motor_power);
}

void drive_left(byte d){
  digitalWrite(motor1_A, d % 2); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B, (d + 1) % 2);
  analogWrite(motor1_Speed, motor_power);
}

void spin_left_new(byte d){
  drive_right(d);
  drive_left(d + 1);
}

void spin_right_new(byte d){
  drive_right(d + 1);
  drive_left(d);
}

void drive_idle(){
  digitalWrite(motor1_A,LOW);
  digitalWrite(motor1_B,LOW);
  analogWrite(motor1_Speed, 0);
  digitalWrite(motor2_A,LOW);
  digitalWrite(motor2_B,LOW);
  analogWrite(motor2_Speed, 0);
}

//TODO: remove old drive functions-------------------------------
void drive_in_current_direction_old(){
  switch (current_drive_status) {
    case D_FORWARD: drive_idle(); drive_forward(); break;
    case D_BACKWARD: drive_idle(); drive_backward(); break;
    case D_LEFT: drive_idle(); drive_left_forward(); break;
    case D_RIGHT: drive_idle(); drive_right_forward(); break;
    case D_SPIN_LEFT: drive_idle(); spin_left(); break;
    case D_SPIN_RIGHT: drive_idle(); spin_right(); break;
    case D_IDLE: drive_idle(); break;
    default: break;
  }
}

void drive_forward(){
  drive_left_forward();
  drive_right_forward(); 
}

void drive_backward(){
  drive_left_backward();
  drive_right_backward();
}

void spin_left(){
  drive_right_backward();
  drive_left_forward();
}

void spin_right(){
  drive_right_forward();
  drive_left_backward();
}

void drive_left_forward(){
  digitalWrite(motor1_A, LOW); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B, HIGH);
  analogWrite(motor1_Speed, motor_power);
}

void drive_right_forward(){
  digitalWrite(motor2_A, HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, LOW);
  analogWrite(motor2_Speed, motor_power);
}

void drive_left_backward(){
  digitalWrite(motor1_A, HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B, LOW);
  analogWrite(motor1_Speed, motor_power);
}

void drive_right_backward(){
  digitalWrite(motor2_A, LOW); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, HIGH);
  analogWrite(motor2_Speed, motor_power);
}
// end of old functions------------------------
