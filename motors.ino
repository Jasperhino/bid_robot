int motor1_A=10;
int motor1_B=8;
int motor1_Speed=A0;
 
int motor2_A=6;
int motor2_B=4;
int motor2_Speed=A1;

#define POWER 255
void setup(){
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  pinMode(motor1_Speed, OUTPUT);
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);
  pinMode(motor2_Speed, OUTPUT);
}
 
void loop(){
  drive_left();
  drive_right();
}

void tes(){
  // motor1
  for (int i=0; i>256; i+=5){
    digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor1_B,LOW);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor1_B,LOW);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  // motor2
  for (int i=0; i<256; i+=5){
    digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor2_B,LOW);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor2_B,LOW);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
 
  // turn vice versa
 
  // motor1
  for (int i=0; i<256; i+=5){
    digitalWrite(motor1_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor1_B,HIGH);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor1_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor1_B,HIGH);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  // motor2
  for (int i=0; i<256; i+=5){
    digitalWrite(motor2_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor2_B,HIGH);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor2_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor2_B,HIGH);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
}

void drive_forward(){
  digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B,LOW);
  analogWrite(motor1_Speed, 255);
  
  digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B,LOW);
  analogWrite(motor2_Speed, 255);
  delay(20);
}

void drive_left(){
  digitalWrite(motor1_A,LOW); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor1_B,HIGH);
  analogWrite(motor1_Speed, 255);
  delay(20);
}

void drive_right(){
  
  digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
  digitalWrite(motor2_B,LOW);
  analogWrite(motor2_Speed, 255);
  delay(20);
}

void spin_left(){
  
}

void spin_right(){
}
