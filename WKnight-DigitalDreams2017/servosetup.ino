 /* Servo setup -
    servosetup()
    pickup()
    putdown()
*/

void servosetup() {
  grabber.write(GRABBER_OPEN);
  lifter2.write(LIFTER_UP);
  lifter.write(LIFTER_UP);
  grabber.attach(8);
  lifter.attach(5);lifter2.attach(9);
}

void pickup() {

  delay(500);
  for (servotmp = LIFTER_UP; servotmp < LIFTER_DOWN; servotmp++) {
    lifter.write(servotmp);lifter2.write(servotmp);
    delay(12);
    
  }

  delay(200);
  for (servotmp = GRABBER_OPEN; servotmp < GRABBER_CLOSE; servotmp++) {
    grabber.write(servotmp);
    delay(12);

  }

  delay(100);
  for (servotmp = LIFTER_DOWN; servotmp > LIFTER_UP; servotmp--) {
    lifter.write(servotmp);lifter2.write(servotmp);
    delay(12);

  }
  
  delay(1000);
}

void putdown() {
  for (servotmp = LIFTER_UP; servotmp < 60; servotmp++) {
    lifter.write(servotmp);lifter2.write(servotmp);
    delay(12);

  }

  for (servotmp = GRABBER_CLOSE; servotmp > GRABBER_OPEN; servotmp--) {
    grabber.write(servotmp);
    delay(12);

  }

  for (servotmp = 60; servotmp > LIFTER_UP; servotmp--) {
    lifter.write(servotmp);lifter2.write(servotmp);
    delay(12);

  }


}
