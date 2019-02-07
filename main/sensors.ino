void readSensors(){
  sensor_buffer_left[buffer_index] = char(analogRead(pin_lightsensor_left));
  sensor_buffer_right[buffer_index] = char(analogRead(pin_lightsensor_right));
  buffer_index++;
  
  if(buffer_index >= BUFFER_SIZE){
    buffer_index = 0;
    byte median_left = median_buffer(sensor_buffer_left);
    byte median_right = median_buffer(sensor_buffer_right);
    
    if(current_mission_status == EXPLORING){
      if(histogram_index < HISTOGRAM_SIZE - 1){
        if(millis() > exploring_sensor_timer + exploring_sensor_interval){
          exploring_sensor_timer = millis();
          histogram[histogram_index] = median_left;
          histogram[histogram_index + 1] = median_right;
          histogram_index += 2;
        }
      } else {
        sort(histogram, HISTOGRAM_SIZE);
        k3_mean(histogram, HISTOGRAM_SIZE);
        current_mission_status = TO_DESTINATION;
        current_drive_status = D_IDLE;
        Serial.println("Finished Exploring");
      }
    } else {
      sensor_old_left = sensor_left;
      sensor_old_right = sensor_right;
      sensor_left = median_left;
      sensor_right = median_right;
    }
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
