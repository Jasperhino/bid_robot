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
      case 'p': print_status(); break;
      default: current_drive_status = D_IDLE; break;
    }
  }
}

void print_status(){
  print_mission_status();
  print_drive_status();
  print_direction();
  print_histogram;
  print_mean_table();
  print_sensors();
  print_buffers();
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
  Serial.print("Drive Status: ");
  Serial.println(result);
}

void print_mission_status() {
  String result = "not a drive status";
  switch (current_mission_status) {
    case EXPLORING: result = "Exploring"; break;
    case TO_DESTINATION: result = "Backward"; break;
    case FINISHED: result = "Finished"; break;
    default: break;
  }
  Serial.print("Mission Status: ");
  Serial.println(result);
}

void print_direction(){
  Serial.print("Direction: ");
  Serial.println(robot_direction);
}

void print_histogram(){
  Serial.print("Hostogram: ");
  print_array(histogram, 200);
}

void print_mean_table(){
  Serial.print("Means: ");
  print_array(mean_table, 3);
}

void print_sensors(){
  Serial.print("Sensor Left: ");
  Serial.println(sensor_left);
  Serial.print("Sensor Right: ");
  Serial.println(sensor_right);

  Serial.print("Sensor Last Left: ");
  Serial.println(sensor_last_left);
  Serial.print("Sensor Last Right: ");
  Serial.println(sensor_last_right);
}

void print_buffers(){
  Serial.print("Buffer Index: ");
  Serial.println(buffer_index);
  Serial.print("Buffer Left: ");
  print_array(sensor_buffer_left, BUFFER_SIZE);
  Serial.print("Buffer Right: ");
  print_array(sensor_buffer_right, BUFFER_SIZE);
}

void print_array(byte table[], int size){
  Serial.print("[");
  for(int i = 0; i < size; i++){
    Serial.print(" ");
    Serial.print(table[i]);
  }
  Serial.println("]");
}
