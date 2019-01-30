int pin_lightsensor_left = A1;
int pin_lightsensor_right = A2;
int pin_led_left = 3;
int pin_led_right = 2;


int data_colection_size=200;

byte* light_data=new byte[data_colection_size];




byte mean_table[3];

void setup() {
  Serial.begin(9600);
  pinMode(pin_lightsensor_left, INPUT_PULLUP);
  pinMode(pin_lightsensor_right, INPUT_PULLUP);
  pinMode(pin_led_left, OUTPUT);
  pinMode(pin_led_right, OUTPUT);
//  collectData();

  test();

}

byte light_val_left;
byte light_val_right;




void test(){
  Serial.println("START");
  byte test[200];
  for (int i = 35; i < 235; i++){
    test[i-35]=i;
  }
  k3_mean(test,200);
  print_array(test,200);

  Serial.println(find_category(123));
  Serial.println("DONE");

  
}

void loop() {
//  updateLightsensors();
//  monitorBrightness();
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
  delay(10);
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
  
  print_array(light_data,200);
  delay(3000);
}


byte find_category(byte point){
  byte dist=abs(point-mean_table[0]);
//  Serial.println(dist);
  if (dist>abs(point-mean_table[1])){
    dist=abs(point-mean_table[1]);
    if (dist>abs(point-mean_table[2])){
      return(2);
    }
    return(1);
  }
  return(0);
}



void k3_mean(byte points[], int size){ 
    
  mean_table[0]=size*0.30;
  mean_table[1]=size*0.50;
  mean_table[2]=size*0.70;



  byte cat_table[size];
  for (int i;i<size;i++){
      cat_table[i]=-1;
  }
    
  bool flag=true;

  while(flag){

    byte white_counter = 0;
    byte grey_counter = 0;
    byte black_counter = 0;
    
    int mean_table_temp[3] = {0,0,0};
    
    print_array(mean_table,3);
    flag=false;
    
    for(int i=0;i<size;i++){
      byte new_category = find_category(points[i]);

     switch (new_category){
      case 0:
        white_counter++;
        break;
      case 1:
        grey_counter++;
        break;
      default:
        black_counter++;
    }
    
      mean_table_temp[new_category]+=points[i];
      
      if (cat_table[i]!=new_category){
        flag=true;
        cat_table[i]=new_category;
      }
    }
    mean_table[0]=mean_table_temp[0]/white_counter;
    mean_table[1]=mean_table_temp[1]/grey_counter;
    mean_table[2]=mean_table_temp[2]/black_counter;
    

    
  }
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

void print_array(byte table[],int size){
//  Serial.println(sizeof(table[0]));
  Serial.print("[");
  for(int i = 0; i < size; i++){
    Serial.print(" ");
    Serial.print(table[i]);
  }
  Serial.println("]");
}
