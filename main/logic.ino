void explore(){
  current_drive_status = D_LEFT;
  if(histogram_index < HISTOGRAM_SIZE / 2){
    current_drive_status = D_RIGHT;
  }
}

void change_direction(){
  if(millis() > change_direction_timer + change_direction_interval){
    change_direction_timer = millis();
    robot_direction = (robot_direction + 1) % 2;
  
    Serial.print("Changed Direction to: ");
    Serial.println(robot_direction);
  }
  
}

bool aligning = false;

void to_destination(){
  category_left = find_category(sensor_left);
  category_right = find_category(sensor_right);

  if(category_left != category_right && !aligning){
    aligning = true;
    if(category_left != old_category_left){
     
      //align right side to left side
      current_drive_status = D_RIGHT;
      
      /*if(((old_category_left + 1 + 3) % 3) == category_left){
        //BAD go back
        change_direction();
      }*/
    } else {      
      //align left side to right side
      current_drive_status = D_LEFT;
      
      /*if(((old_category_right + 1 + 3) % 3) == category_right){
        //BAD go back
        change_direction();
      }*/
    }
  } else {
    
    if(((old_category_right + 1 + 3) % 3) == category_right && aligning){
        //BAD go back
        change_direction();
    }
    aligning = false;
    current_drive_status = D_FORWARD;
    old_category_left = category_left;
    old_category_right = category_right;
  }
  
}

void change_to_exploring(){
    histogram_index = 0;
    current_mission_status = EXPLORING;
}
