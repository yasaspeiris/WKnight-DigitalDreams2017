void materialdetectionsetup(){
  
}

void decidematerial(){
  int value = analogRead(A10);
  if (value >700){
    material = 'A';
  }else{
    material = 'P';
  }
}
