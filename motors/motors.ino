int pin_lightsensor_left = A2;
int pin_lightsensor_right = A3;

int motor1_A=10;
int motor1_B=8;
int motor1_Speed=A0;
 
int motor2_A=6;
int motor2_B=4;
int motor2_Speed=A1;

byte motor_power = 255;
bool pwm_on = false;
int motor_pwm_on = 10;
int motor_pwm_off = 10;
long motor_on_timer;
long motor_off_timer;

long brain_timer = 0;
long brain_time = 1000;

enum drive_status : byte {
  D_LEFT,
  D_RIGHT,
  D_SPIN_LEFT,
  D_SPIN_RIGHT,
  D_FORWARD,
  D_BACKWARD,
  D_IDLE
};

drive_status current_drive_status = D_IDLE;

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

  motor_on_timer = millis();
  motor_off_timer = millis() + motor_pwm_on; 
}
 
void loop(){
  readSerial();
  //brain();
  drive();
}

void brain(){
  //Serial.println(brain_timer);
  if(millis() > brain_timer + brain_time){
    current_drive_status = testdrive[dindex];
    //print_drive_status();
    dindex++;
    if(dindex > 6) dindex = 0;
    brain_timer = millis();
  }
}

void drive() {
 if(!pwm_on){
  drive_in_current_direction();
  return;
 }
 if(millis() > motor_off_timer){
  drive_idle();
  motor_off_timer = millis() + motor_pwm_on + motor_pwm_off;
 }
 if(millis() > motor_on_timer){
  drive_in_current_direction();
  motor_on_timer = millis() + motor_pwm_on + motor_pwm_off;
 }
}

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

//Debugging
void readSerial(){
  if(Serial.available() > 0) {
    byte b = Serial.read();
    switch(b) {
      case 'w': current_drive_status = D_FORWARD; break;
      case 'a': current_drive_status = D_LEFT; break;
      case 's': current_drive_status = D_BACKWARD; break;
      case 'd': current_drive_status = D_RIGHT; break;
      case 'e': current_drive_status = D_SPIN_RIGHT; break;
      case 'q': current_drive_status = D_SPIN_LEFT; break;
      default: current_drive_status = D_IDLE; break;
    }
    print_drive_status();
  }
}
