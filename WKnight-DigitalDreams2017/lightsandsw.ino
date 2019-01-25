void lightsandswsetup() {
  pinMode(STARTSWITCH, INPUT);
  pinMode(MODESW, INPUT);

  pinMode(BLUELED1, OUTPUT);
  //pinMode(YELLOWLED, OUTPUT);
  pinMode(BLUELED2, OUTPUT);
  

  digitalWrite(BLUELED1, HIGH);
  //digitalWrite(YELLOWLED, HIGH);
}
