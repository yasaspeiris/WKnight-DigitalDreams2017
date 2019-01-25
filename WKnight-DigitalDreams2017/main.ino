void setup() {
  Serial.begin(115200);
  motorsetup();
  servosetup();
  lightsandswsetup();

}

void loop() {
  // put your main code here, to run repeatedly:
  int val1 = digitalRead(STARTSWITCH);
  int val2 = digitalRead(MODESW);
  if ( val1 == 0) {
    delay(500);
    executesecondroundpath();


  } if (val2 == 0) {
    digitalWrite(BLUELED2, HIGH);
    QTRCcallibrate();
    digitalWrite(BLUELED2, LOW);
  }
}
