byte buffer_index = 0;
byte memory_index = 0;

void readSensors(){
  sensor_val_left = char(analogRead(pin_lightsensor_left));
  sensor_val_right = char(analogRead(pin_lightsensor_right));
  buffer_index++;
  
  if(buffer_index >= BUFFER_SIZE){
    buffer_index = 0;
    
    sensor_left_memory[memory_index] = average_buffer(sensor_left_buffer);
    sensor_right_memory[memory_index] = average_buffer(sensor_right_buffer);
    memory_index++;
    
    if(memory_index >= MEMORY_SIZE){
      memory_index = 0;
    }
  }
  
  if(log_sensors){
    Serial.print("Left: ");
    Serial.print(sensor_val_left);
    Serial.print(" - ");
    Serial.print("Right: ");
    Serial.println(sensor_val_right);
  }
}

byte average_buffer(byte b[]) {
  int sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++){
    sum += b[i];
  }
  return char(sum / BUFFER_SIZE);
}

byte getMemoryAt(byte b[], int i){
  return b[((i + MEMORY_SIZE) % MEMORY_SIZE)];
}
