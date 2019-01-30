int pin_lightsensor_left = A2;
int pin_lightsensor_right = A3;

int motor1_A=10;
int motor1_B=8;
int motor1_Speed=A0;
 
int motor2_A=6;
int motor2_B=4;
int motor2_Speed=A1;

int motor_power = 130;
int motor_speed = 0;

enum drive_status : byte {
  D_LEFT,
  D_RIGHT,
  D_FORWARD,
  D_BACKWARD,
  D_IDLE
};

enum drive_direction : byte {
  NORTH,
  SOUTH
};

drive_status current_drive_status = D_IDLE;

drive_status testdrive[] = {D_IDLE, D_FORWARD, D_BACKWARD, D_LEFT, D_RIGHT};
byte dindex = 0;

void setup(){
  Serial.begin(9600);
  pinMode(pin_lightsensor_left, INPUT_PULLUP);
  pinMode(pin_lightsensor_right, INPUT_PULLUP);
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  pinMode(motor1_Speed, OUTPUT);
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);
  pinMode(motor2_Speed, OUTPUT);
}
 
void loop(){
  //readSerial();
  brain();
  drive();
  delay(1000);
}

void brain(){
  current_drive_status = testdrive[dindex];
  dindex++;
  if(dindex > 4) dindex = 0;
}

void readSerial(){
  if(Serial.available() > 0) {
    byte b = Serial.read();
    switch(b) {
      case 'w': current_drive_status = D_FORWARD; break;
      case 'a': current_drive_status = D_LEFT; break;
      case 's': current_drive_status = D_BACKWARD; break;
      case 'd': current_drive_status = D_RIGHT; break;
      default: current_drive_status = D_IDLE; break;
    }
    Serial.print("DRIVING_STATUS: ");
    Serial.println(get_drive_status_string(current_drive_status));
  }
}

void drive() {
  switch (current_drive_status) {
    case D_FORWARD: drive_forward(); break;
    case D_BACKWARD: drive_backward(); break;
    case D_LEFT: spin_left(); break;
    case D_RIGHT: spin_right(); break;
    case D_IDLE: drive_idle(); break;
    default: break;
  }
}

void drive_forward(){
  drive_left(NORTH);
  drive_right(NORTH);
}

void drive_backward(){
  drive_left(SOUTH);
  drive_right(SOUTH);
}

void drive_left(drive_direction d){
  byte a = LOW;
  byte b= HIGH;
  if(d == SOUTH){
    a = HIGH; b = LOW;
  }
  digitalWrite(motor1_A,a); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B,b);
  analogWrite(motor1_Speed, motor_power);
}

void drive_right(drive_direction d){
    byte a = HIGH;
    byte b = LOW;
  if(d == SOUTH){
    a = LOW; b = HIGH;
  }
  digitalWrite(motor2_A, a); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B, b);
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

void spin_left(){
  drive_right(SOUTH);
  drive_left(NORTH);
}

void spin_right(){
  drive_right(NORTH);
  drive_left(SOUTH);
}

String get_drive_status_string (drive_status ds) {
  String result = "not a drive status";
  switch (ds) {
    case D_FORWARD: result = "Forward"; break;
    case D_BACKWARD: result = "Backward"; break;
    case D_LEFT: result = "Left"; break;
    case D_RIGHT: result = "Right"; break;
    case D_IDLE: result = "Idle"; break;
  }
  return result;
}
