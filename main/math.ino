byte mean_table[3];

byte find_category(byte point){
  byte dist = abs(point - mean_table[0]);
//  Serial.println(dist);
  if (dist > abs(point-mean_table[1])){
    dist = abs(point-mean_table[1]);
    if (dist > abs(point-mean_table[2])){
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
