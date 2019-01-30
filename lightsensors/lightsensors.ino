int pin_lightsensor_left = A0;
int pin_lightsensor_right = A1;
int pin_led_left = 3;
int pin_led_right = 8;

#define BUFFERSIZE 6
byte sensor_left_memory [BUFFERSIZE];
byte sensor_right_memory [BUFFERSIZE];

byte threshhold_upper = 70;
byte threshhold_lower = 140;

int index = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pin_lightsensor_left, INPUT_PULLUP);
  pinMode(pin_lightsensor_right, INPUT_PULLUP);
  pinMode(pin_led_left, OUTPUT);
  pinMode(pin_led_right, OUTPUT);
}

byte light_val_left;
byte light_val_right;

void loop() {
  updateLightsensors();
  monitorBrightness();
}

void monitorBrightness(){
  analogWrite(pin_led_left, light_val_left);
  analogWrite(pin_led_right, light_val_right);
}

void updateLightsensors(){
  light_val_left = char(analogRead(pin_lightsensor_left));
  light_val_right = char(analogRead(pin_lightsensor_right));
  Serial.print("Left: ");
  Serial.print(light_val_left);
  Serial.print(" - ");
  Serial.print("Right: ");
  Serial.println(light_val_right);
}

void collectData(){
    for (int i = 0; i < BUFFERSIZE; i++){
    updateLightsensors();
    printBuffer(sensor_left_memory);
    Serial.println("-----------------------------");
    printBuffer(sensor_right_memory);
    blinkBothLEDs();
    index++;
  }
}

void printBuffer(const byte a[]){
  for ( int i = 0; i < BUFFERSIZE; ++i ) {
    Serial.print(a[i]);
    Serial.print(";");
  }
}

void blinkBothLEDs(){
  digitalWrite(pin_led_left, HIGH);
  digitalWrite(pin_led_right, HIGH);
  delay(500);
  digitalWrite(pin_led_left, LOW);
  digitalWrite(pin_led_right, LOW);
  delay(500);  
}
