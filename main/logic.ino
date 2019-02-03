byte type_left = -1;
byte type_right = -1;

void to_destination(){
  bool go_backwards = false;

  byte new_type_left = find_category(sensor_last_left);
  byte new_type_right = find_category(sensor_last_right);

  if(type_left != type_right){
    if(new_type_left != type_left){

      //align right side to left side
      drive_right_forward();
      
      if(((type_left+3)%3)-1 == new_type_left){
        //GOOD go on
      } else {
        //BAD go back
        go_backwards = true;
      }

      
    } else {

      //align left side to right side

      
      if(((type_right+3)%3)-1==new_type_right){
        //GOOD go on
      }else{
        //BAD go back
      }
    }
  }
}

void explore(){
  if(millis() < exploring_timer + (exploring_interval / 2)){
    spin_right();
  } else {
    spin_left();
  }
  
  if(millis() > exploring_timer + exploring_interval){
    current_mission_status == TO_DESTINATION;
    drive_idle();
  }
}
