void drive_in_current_direction(){
  switch (current_drive_status) {
    case D_FORWARD: drive_forward(); break;
    case D_BACKWARD: drive_backward(); break;
    case D_LEFT: drive_left_forward(); break;
    case D_RIGHT: drive_right_forward(); break;
    case D_SPIN_LEFT: spin_left(); break;
    case D_SPIN_RIGHT: spin_right(); break;
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
  digitalWrite(motor1_A,LOW); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B,HIGH);
  analogWrite(motor1_Speed, motor_power);
}

void drive_left_backward(){
  digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B,LOW);
  analogWrite(motor1_Speed, motor_power);
}

void drive_right_forward(){
  digitalWrite(motor2_A, HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, LOW);
  analogWrite(motor2_Speed, motor_power);
}

void drive_right_backward(){
  digitalWrite(motor2_A, LOW); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, HIGH);
  analogWrite(motor2_Speed, motor_power);
}

void drive_idle(){
  digitalWrite(motor1_A,LOW);
  digitalWrite(motor1_B,LOW);
  analogWrite(motor1_Speed, 0);
  digitalWrite(motor2_A,LOW);
  digitalWrite(motor2_B,LOW);
  analogWrite(motor2_Speed, 0);
}
void print_drive_status() {
  String result = "not a drive status";
  switch (current_drive_status) {
    case D_FORWARD: result = "Forward"; break;
    case D_BACKWARD: result = "Backward"; break;
    case D_LEFT: result = "Left"; break;
    case D_RIGHT: result = "Right"; break;
    case D_SPIN_LEFT: result = "Spin Left"; break;
    case D_SPIN_RIGHT: result = "Spin Right"; break;
    case D_IDLE: result = "Idle"; break;
    default: break;
  }
  Serial.println(result);
}
