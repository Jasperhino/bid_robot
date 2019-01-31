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

void print_array(byte table[], int size){
  Serial.print("[");
  for(int i = 0; i < size; i++){
    Serial.print(" ");
    Serial.print(table[i]);
  }
  Serial.println("]");
}
