//PINS
int pin_lightsensor_left = A2;
int pin_lightsensor_right = A3;

int motor1_A = 10;
int motor1_B = 8;
int motor1_Speed = A0;
 
int motor2_A = 6;
int motor2_B = 4;
int motor2_Speed = A1;

//CONSTANTS
enum drive_status : byte {
  D_LEFT,
  D_RIGHT,
  D_SPIN_LEFT,
  D_SPIN_RIGHT,
  D_FORWARD,
  D_BACKWARD,
  D_IDLE
};

enum mission_status : byte {
  EXPLORING,
  TO_DESTINATION,
  FINISHED
};

//SETTINGS
mission_status current_mission_status = EXPLORING;
drive_status current_drive_status = D_IDLE;

byte motor_power = 255;
bool pwm_on = false;
int motor_pwm_on = 10;
int motor_pwm_off = 10;

bool log_sensors = false;

//PHASE TIMER
long exploring_interval = 5000;
long exploring_timer;

long finish_interval = 2000;
long turn_timer;

//PSEUDO MULTITHREADING TIMERS
long motor_on_timer;
long motor_off_timer;

long brain_timer;
long brain_interval = 1000;

//MEMORY
//TODO: do i need this?
byte sensor_val_left;
byte sensor_val_right;

byte histogram [200];
int histogram_index = 0;

#define BUFFER_SIZE 5
#define MEMORY_SIZE 20
byte sensor_left_buffer [BUFFER_SIZE];
byte sensor_right_buffer [BUFFER_SIZE];
byte sensor_left_memory [MEMORY_SIZE];
byte sensor_right_memory [MEMORY_SIZE];

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

  //start timers
  motor_on_timer = millis();
  motor_off_timer = millis() + motor_pwm_on;
  brain_timer = millis();
  exploring_timer = millis();
}

void loop(){
  readSensors();
  brain();
  drive();
}

void brain(){
  if(millis() > brain_timer + brain_interval){
    brain_timer = millis();

    if(mission_status == EXPLORING){
      if(millis() > exploring_timer + exploring_interval){
        current_mission_status == TO_DESTINATION; return
      }
    }

    if(mission_status == TO_DESTINATION){
      to_destination();
    }

    if (mission_status == FINISHED){
      //We are DONE
      Serial.println("DONE!")
    }
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