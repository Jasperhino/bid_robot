void readSensors(){
  sensor_buffer_left[buffer_index] = char(analogRead(pin_lightsensor_left));
  sensor_buffer_right[buffer_index] = char(analogRead(pin_lightsensor_right));
  buffer_index++;
  
  if(buffer_index >= BUFFER_SIZE){
    buffer_index = 0;
    byte median_left = median_buffer(sensor_buffer_left);
    byte median_right = median_buffer(sensor_buffer_right);
    
    if(current_mission_status == EXPLORING){
      histogram[histogram_index] = median_left;
      histogram[histogram_index + 1] = median_right;
      
    } else {
      sensor_last_left = sensor_left;
      sensor_last_right = sensor_right;
      sensor_left = median_left;
      sensor_right = median_right;
    }
  }
  
  if(log_sensors){
    Serial.print("Left: ");
    Serial.print(sensor_left);
    Serial.print(" - ");
    Serial.print("Right: ");
    Serial.println(sensor_right);
  }
}

byte average_buffer(byte b[]) {
  int sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++){
    sum += b[i];
  }
  return char(sum / BUFFER_SIZE);
}

byte median_buffer(byte b[]) {
  sort(b, BUFFER_SIZE);
  return b[(BUFFER_SIZE + 1) / 2];
}

byte getMemoryAt(byte b[], int i){
  return b[((i + MEMORY_SIZE) % MEMORY_SIZE)];
}
