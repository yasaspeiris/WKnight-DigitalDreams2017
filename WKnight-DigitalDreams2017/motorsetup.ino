/*Motor driver functions -
   contains -
    motorsetup() - always run at setup
    SetMasterPower(int MasterPower) - set Master(left) pwm + front - back
    SetSlavePower (int SlavePower) - set Slave(right) pwm + front - back
    inchtravel(int distance,int +-power) - encoded movementfor provided inches/10
    MaintainMovement() - only run inside mmtravel,inchtravel,sharpleft or sharpright,angleturn
    StopMovement() - stop motors
*/

void motorsetup() {
  // put your setup code here, to run once:
  pinMode(LMOTORSPEED, OUTPUT); pinMode(RMOTORSPEED, OUTPUT);
  analogWrite(LMOTORSPEED, 0); analogWrite(RMOTORSPEED, 0);

  pinMode(RMOTOR1, OUTPUT); pinMode(RMOTOR2, OUTPUT);
  digitalWrite(RMOTOR1, LOW); digitalWrite(RMOTOR2, LOW);

  pinMode(LMOTOR1, OUTPUT); pinMode(LMOTOR2, OUTPUT);
  digitalWrite(LMOTOR1, LOW); digitalWrite(LMOTOR2, LOW);

  pinMode(MOTOREN, OUTPUT);
  digitalWrite(MOTOREN, HIGH);

  pinMode(MOTOREN2, OUTPUT);
  digitalWrite(MOTOREN2, HIGH);

  pinMode(LMOTORSF, INPUT); pinMode(RMOTORSF, INPUT);
  pinMode(RMOTORCS, INPUT); pinMode(LMOTORCS, INPUT);


}
/*===========================================================

  Node Clear

   ===========================================================
*/



/*===========================================================

  Set PWM - Set Master and Slave PWM - Master - Left Wheel

   ===========================================================
*/
void SetMasterPower(int MasterPower) {
  if (MasterPower < 0) {
    analogWrite(LMOTORSPEED, abs(MasterPower));
    digitalWrite(LMOTOR1, HIGH); digitalWrite(LMOTOR2, LOW);

  } else if (MasterPower > 0) {
    analogWrite(LMOTORSPEED, abs(MasterPower));
    digitalWrite(LMOTOR1, LOW); digitalWrite(LMOTOR2, HIGH);

  } else {
    digitalWrite(LMOTOR1, LOW ); digitalWrite(LMOTOR2, LOW);
  }
}

void SetSlavePower(int SlavePower) {
  if (SlavePower < 0) {
    analogWrite(RMOTORSPEED, abs(SlavePower));

    digitalWrite(RMOTOR1, HIGH); digitalWrite(RMOTOR2, LOW);

  } else if (SlavePower > 0) {
    analogWrite(RMOTORSPEED, abs(SlavePower));
    digitalWrite(RMOTOR1, LOW); digitalWrite(RMOTOR2, HIGH);

  } else {
    digitalWrite(RMOTOR1, LOW); digitalWrite(RMOTOR2, LOW);
  }
}


/*===========================================================

  Distance Travel Commands --inchtravel(supply inches in tenths mmtravel
  inchtravel - provide distance power and direction
  mmtravel - provide distance power and direction
  nodetravel - travel till next node

   ===========================================================
*/

/*===================================================================

          // Line - nodetravel,nodetravelnostop, linetravel,alligntoline

  ===================================================================== */

void nodetravel(int power) { //nodetravel won't stop motors on its own. needs stopmovement to be called externally.
  nodeflag = 0;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0; SensorPanelVal = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;
  while (nodeflag == 0) {
    MaintainLineMovement();
  }
  StopMovement();
  MaxPower = 0;
}

void nodetravelnostop(int power) { //nodetravel won't stop motors on its own. needs stopmovement to be called externally.
  nodeflag = 0;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0; SensorPanelVal = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;
  while (nodeflag == 0) {
    MaintainNoStopLineMovement();
  }
}

void linetravel(int distance, int power) {
  int tickGoal = (128 * (distance)); int i;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;

  while (abs(totalTicks) <  tickGoal) {
    MaintainLineMovement();

  }
  StopMovement(); //StopMotors
}

void alligntolinebyleft() {
  QTRCRead();
  if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
    SetMasterPower(-70); SetSlavePower(70);
    while (1) {
      QTRCRead();
      if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
        break;
      }
    }
    StopMovement();
  }
}

void alligntolinebyright() {
  QTRCRead();
  if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
    SetMasterPower(70); SetSlavePower(-70);
    while (1) {
      QTRCRead();
      if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
        break;
      }
    }
    StopMovement();
  }
}

/*===================================================================

          // Encoder travel - inchtravel, inchtravelnostop,mmtravel

  ===================================================================== */
void inchtravel(float distance, int power) {
  int tickGoal = (128 * (distance)); int i;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;

  while (abs(totalTicks) <  tickGoal) {
    MaintainMovement();

  }
  StopMovement(); //StopMotors
}

void inchtravelnostop(int distance, int power) {//only run inside node travel no stop
  int tickGoal = (128 * (distance)); int i;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;

  while (abs(totalTicks) <  tickGoal) {
    MaintainMovement();

  }
  //StopMovement(); //StopMotors
}

void mmtravel(int distance, int power) {
  int tickGoal = tickspermm * distance;
  MasterPower = power; SlavePower = power;
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0;

  while (abs(totalTicks) <  tickGoal) {
    MaintainMovement();//Go straight maintaining heading
  }
  StopMovement(); //StopMotors
}

/*===================================================================

          // Degree Travel - degreetravel

  ===================================================================== */

void degreetravel(int degree, int power) {
  int tickGoal = abs(degree) * 6.5;//compensation
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0;
  if (degree > 0) { //left turn
    SetMasterPower(-1 * power); SetSlavePower(power);
    while (MasterENC.read() > (-1 * tickGoal) || SlaveENC.read() < tickGoal) {

    }
    StopMovement();
  } else if (degree < 0) {
    MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0;
    SetMasterPower( power); SetSlavePower(-power);
    while (MasterENC.read() < tickGoal || SlaveENC.read() > (-1 * tickGoal)) {

    }
    StopMovement();
  }

}




/*===========================================================

  Line Movement - maintainlinemovment

   ===========================================================
*/
void MaintainLineMovement() { //Only run inside nodetravel
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
  QTRCRead();
  //Serial.println(position);
  error =  (int)position - 3500 ;
  //Serial.println(error);
  int delta = error - lasterror;
  int change = (error * 2.4) + (delta * 27.7);
  lasterror = error;
  const int maxchange = 140;
  if (change > maxchange) {
    change = maxchange;
  }
  if (change < -maxchange) {
    change = -maxchange;
  }

  MasterPower = MaxPower - change;
  MasterPower = constrain(MasterPower, 0, 220);
  SlavePower  = MaxPower + change;
  SlavePower = constrain(SlavePower, 0, 220);


  Serial.print("Slave = "); Serial.println(SlavePower); Serial.print("Master = "); Serial.println(MasterPower);
  totalTicks += MasterENC.read(); MasterENC.write(0); SlaveENC.write(0);



  if (SensorPanelVal == 15  ||  SensorPanelVal == 31  ||  SensorPanelVal == 63) {
    nodeflag = 1;//right turn
    StopMovement();
  } else if (SensorPanelVal == 240  ||  SensorPanelVal == 248  ||  SensorPanelVal == 252) {
    nodeflag = 1; // left turn
    StopMovement();
  } else if (SensorPanelVal == 255) {
    nodeflag = 1; //T
    StopMovement();
  }
}

void MaintainNoStopLineMovement() { //Only run inside nodetravelnostop
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
  QTRCRead();
  //Serial.println(position);
  error =  (int)position - 3500 ;
  //Serial.println(error);
  int delta = error - lasterror;
  int change = (error * 2.4) + (delta * 25.7);
  lasterror = error;
  const int maxchange = 140;
  if (change > maxchange) {
    change = maxchange;
  }
  if (change < -maxchange) {
    change = -maxchange;
  }

  MasterPower = MaxPower - change;
  MasterPower = constrain(MasterPower, 0, 220);
  SlavePower  = MaxPower + change;
  SlavePower = constrain(SlavePower, 0, 220);

  totalTicks += MasterENC.read(); MasterENC.write(0); SlaveENC.write(0);



  if (SensorPanelVal == 15  ||  SensorPanelVal == 31  ||  SensorPanelVal == 63) {
    nodeflag = 1;//right turn
    inchtravelnostop(2, 140);
  } else if (SensorPanelVal == 240  ||  SensorPanelVal == 248  ||  SensorPanelVal == 252) {
    nodeflag = 1; // left turn
    inchtravelnostop(2, 140);
  } else if (SensorPanelVal == 255) {
    nodeflag = 1; //T
    inchtravelnostop(2, 140);

  }
}



/*===========================================================

  Encoder Movement - MaintainMovement

   ===========================================================
*/


void MaintainMovement() { //Only run inside inchtravel,mmtravel,sharpleft,sharpright
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
  int wallcorrection = 0;

  error =  (MasterENC.read()) - (SlaveENC.read());
  int delta = error - lasterror;
  SlavePower += (error * 0.45) + (delta * 0.2); //+ (wallcorrection * 10);
  totalTicks += MasterENC.read(); MasterENC.write(0); SlaveENC.write(0);
  lasterror = error;
  delay(20);
}

/*===========================================================

  Stop Commands

   ===========================================================
*/


void StopMovement() {
  //breaking
  digitalWrite(RMOTOR1, LOW); digitalWrite(RMOTOR2, LOW);
  digitalWrite(LMOTOR1, LOW); digitalWrite(LMOTOR2, LOW);
  analogWrite(LMOTORSPEED, 100); analogWrite(RMOTORSPEED, 100);
  delay(50);
  MasterPower = 0; SlavePower = 0;
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
}

void HardStop() {
  //HARDY HAR HARD breaking

  digitalWrite(RMOTOR1, LOW); digitalWrite(RMOTOR2, LOW);
  digitalWrite(LMOTOR1, LOW); digitalWrite(LMOTOR2, LOW);
  analogWrite(LMOTORSPEED, 255); analogWrite(RMOTORSPEED, 255);
  delay(50);
  MasterPower = 0; SlavePower = 0;
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
}

void CoastMovement() {
  MasterPower = 0; SlavePower = 0;
  SetMasterPower(MasterPower); SetSlavePower(SlavePower);
}
