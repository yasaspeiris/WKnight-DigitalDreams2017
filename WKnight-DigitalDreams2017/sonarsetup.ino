void getdistance() {
  int i = 0;
  for (i = 0; i<5 ; i++){
    pingfront(); 
    tmp += front; 
  }
  front  = front / 5;
  
}

void pingfront() {
  front = (sonar.ping()/58);
  delay(10);
}
