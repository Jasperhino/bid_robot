int pin_lightsensor_left = A1;
int pin_lightsensor_right = A2;
int pin_led_left = 3;
int pin_led_right = 2;


byte light_data[200];

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
  collectData();
  updateLightsensors();
  monitorBrightness();
  
}

void monitorBrightness(){
  if (light_val_left-light_val_right < -9){
    analogWrite(pin_led_left, 200);
  }else{
    analogWrite(pin_led_left, 0);
  }
  
  if (light_val_left-light_val_right > 9){
    analogWrite(pin_led_right, 200);
  }else{
    analogWrite(pin_led_right, 0);
  }
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
   analogWrite(pin_led_left, 200);
   analogWrite(pin_led_right, 200);
   for (int i = 0; i < 200; i=i+2){
    delay(50);
    updateLightsensors();
    light_data[i]=light_val_left;
    light_data[i+1]=light_val_right;
  }
  analogWrite(pin_led_left, 0);
  analogWrite(pin_led_right, 0);
  
  sort(light_data,200);
  
  print_array(light_data);
  delay(3000);
}


void sort(byte a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    byte t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

void print_array(byte table[]){
  Serial.println(sizeof(table[0]));
  Serial.print("[");
  for(int i = 0; i < 200; i++){
    Serial.print(" ");
    Serial.print(table[i]);
  }
  Serial.print("]");
}
