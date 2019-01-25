void QTRCcallibrate() {
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode

  for (int i = 0; i < 50; i++)  // make the calibration take about 10 seconds
  {
    if (i  < 15 || i >= 35) { // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
      SetMasterPower(-70); SetSlavePower(70);
    } else {
      SetMasterPower( 70); SetSlavePower(-70);
    } qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  StopMovement();
  delay(300);

  for (int i = 0; i < 50; i++)  // make the calibration take about 10 seconds
  {
    if (i  < 15 || i >= 35) { // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
      SetMasterPower(-70); SetSlavePower(70);
    } else {
      SetMasterPower( 70); SetSlavePower(-70);
    } qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  StopMovement();
  delay(300);

  for (int i = 0; i < 50; i++)  // make the calibration take about 10 seconds
  {
    if (i  < 15 || i >= 35) { // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
      SetMasterPower(-70); SetSlavePower(70);
    } else {
      SetMasterPower( 70); SetSlavePower(-70);
    } qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  StopMovement();
  delay(300);

  for (int i = 0; i < 50; i++)  // make the calibration take about 10 seconds
  {
    if (i  < 15 || i >= 35) { // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
      SetMasterPower(-70); SetSlavePower(70);
    } else {
      SetMasterPower( 70); SetSlavePower(-70);
    } qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  StopMovement();
  MasterENC.write(0);SlaveENC.write(0);
  delay(300);
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void QTRCRead() {
  position = qtrrc.readLine(sensorValues);

  for (int x=0;x<8;x++){
     sensorRead[x] = sensorValues[x];
     //Serial.print(sensorValues[x]);
     //Serial.print("    ");
  } 
  
  for (int i=0;i<8;i++){
     if (sensorRead[i] > 700){
       sensorRead[i]=1;
       
     }else{ 
       sensorRead[i]=0;
     }   
  }

  SensorPanelVal = (sensorRead[0]*1) + (sensorRead[1]*2) + (sensorRead[2]*4) + (sensorRead[3]*8) + (sensorRead[4]*16) + (sensorRead[5]*32) + (sensorRead[6]*64) + (sensorRead[7]*128);    
   Serial.println(SensorPanelVal);
 
}

void DetectNode() {

}
