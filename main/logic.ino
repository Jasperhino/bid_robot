void explore(){
  current_drive_status = D_SPIN_LEFT;
  if(histogram_index < HISTOGRAM_SIZE / 2){
    current_drive_status = D_SPIN_RIGHT;
  }
}

void to_destination(){
  byte category_left = find_category(sensor_left);
  byte category_right = find_category(sensor_right);
  byte old_category_left = find_category(sensor_old_left);
  byte old_category_right = find_category(sensor_old_right);

  if(category_left != category_right){
    old_category = category;
    if(category_left != old_category_left){
      
      category = category_left;
      //align right side to left side
      current_drive_status = D_RIGHT;
      
      if(((old_category_left + 1 + 3) % 3) == category_left){
        //BAD go back
        change_direction();
      }      
    } else {
      category = category_right;
      
      //align left side to right side
      current_drive_status = D_LEFT;
      
      if(((old_category_right + 1 + 3) % 3) == category_right){
        //BAD go back
        change_direction();
      }
    }
  } else {
    category = category_left;
    current_drive_status = D_FORWARD;
  }
}

void change_to_exploring(){
    histogram_index = 0;
    current_mission_status = EXPLORING;
}
