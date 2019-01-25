void executemovement(char path[20]) { // pass pre-defined paths to this
  int i = 0;
  while (path[i] != 'E') {

    if (path[i] == 'N') {
      nodetravel(160);
      delay(150); // delay to clear intersection??
      inchtravel(1, 120);
      delay(150);
    }

    if (path[i] == 'G') {
      nodetravelnostop(160);
    }

    else if ( path[i] == 'P') {
      linetravel(LINE1INCHES, 160);
      delay(150);

    }

    else if ( path[i] == 'Q') {
      linetravel(LINE2INCHES, 160);
      delay(150);

    }

    else if ( path[i] == 'L') {
      degreetravel(80, 120);
      delay(50);
      QTRCRead();
      if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
        SetMasterPower(-60); SetSlavePower(60);
        while (1) {
          QTRCRead();
          if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
            break;
          }
        }
        StopMovement();
      }
      delay(150);
    }

    else if ( path[i] == 'R') {
      degreetravel(-80, 120);
      delay(50);
      QTRCRead();
      if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
        SetMasterPower(60); SetSlavePower(-60);
        while (1) {
          QTRCRead();
          if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
            break;
          }
        }
        StopMovement();
      }
      delay(150);
    }

    else if ( path[i] == 'T') {
      degreetravel(200, 120);
      delay(50);
      QTRCRead();
      if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
        SetMasterPower(-60); SetSlavePower(60);
        while (1) {
          QTRCRead();
          if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
            break;
          }
        }
        StopMovement();
      }
      delay(150);
    }

    else if (path [i] == 'C') {
      for (int m = 0; m < 5; m++) {
        pingfront();
        degreetravel(1, 100);
        if (front > 0) {
          //alligntolinebyright();
          int fronterror = 16 - front;
          if (fronterror > 0) {
            mmtravel(fronterror*5.9, -100);
          }else{
            mmtravel(-1*fronterror*5.9,100);
          }
          pickup();
          decidematerial();
          isballfound = 1;
          break;
        }
      }

      if (isballfound == 0) {
        for (int m = 0; m < 15; m++) {
          pingfront();
          degreetravel(-1, 100);
          delay(10);
          if (front > 0) {
            //alligntolinebyleft();
            int fronterror = 16 - front;
          if (fronterror > 0) {
            mmtravel(fronterror*5.9, -100);
          }else{
            mmtravel(-1*fronterror*5.9,100);
          }
            //alligntoline();
            pickup();
            decidematerial();
            isballfound = 1;
            break;
          }
        }
      }
      nodetravel(160);
      delay(150);
      inchtravel(1.5, 100);
      delay(150);
    }



    else if (path[i] == 'D') {
      linetravel(14, 160);
      delay(150);
      //adjust to front
      putdown();
      delay(150);
      inchtravel(2,-120);
      delay(150);
    }
    else if (path[i] == 'M') {
      mmtravel(10, 100);
      delay(50);
      QTRCRead();
      if (SensorPanelVal != 24  ||  SensorPanelVal != 48  ||  SensorPanelVal != 96) {
        SetMasterPower(60); SetSlavePower(-60);
        while (1) {
          QTRCRead();
          if (SensorPanelVal == 24  ||  SensorPanelVal == 48  ||  SensorPanelVal == 96) {
            break;
          }
        }
        StopMovement();
      }
      delay(300);
    }
    else if (path[i] == 'K') {
      nodetravel(120);
      delay(200);
      inchtravel(3,120);
      delay(200);
      
    }
    i++;
  }
  currentpos = path[i + 1]; //save last element in char array as current pos

}

void executefirstroundpath() { //pass default poi or identified poi
  inchtravelnostop(3, 140); // clear start box
  while (isballfound == 0) {//traverse pois till ball is found
    if (currentpos == 's') {
      executemovement(StartToN8); //default movement from start
    } else if (currentpos == 'a') {
      executemovement(N3ToN5);
    } else if ( currentpos == 'b') {
      executemovement(N5ToN6);
    } else if ( currentpos == 'c') {
      executemovement(N6ToN8);
    } else if ( currentpos == 'd') {
      executemovement(N8ToN9);
    } else if (currentpos == 'e')
      executemovement(N9ToN10);
  }
  firstroundballpos = currentpos;

  //deliver ball to goal entrance - N4
  if (currentpos == 'a') {
    executemovement(N3ToN4);
  } else if ( currentpos == 'b') {
    executemovement(N5ToN4);
  } else if ( currentpos == 'c') {
    executemovement(N6ToN4);
  } else if ( currentpos == 'd') {
    executemovement(N8ToN4);
  } else if (currentpos == 'e') {
    executemovement(N9ToN4);
  } else if (currentpos == 'f') {
    executemovement(N10ToN4);
  }

  //deliver ball to Alu or Plastic Container
  if (material == 'A') {
    executemovement(N4ToAlu);
    executemovement(AluToEnd);
  } else if (material == 'P') {
    executemovement(N4ToPlastic);
    executemovement(PlasticToEnd);
  }

  inchtravel(4, 120);
}

void firstroundquickfinish() {
  currentpos = 's'; isballfound = 0; material = 'n';
  inchtravel(3, 140);
  if (firstroundballpos == 'a') {
    executemovement(StartToN3);
  } else if ( firstroundballpos == 'b') {
    executemovement(StartToN5);
  } else if ( firstroundballpos == 'c') {
    executemovement(StartToN6);
  } else if ( firstroundballpos == 'd') {
    executemovement(StartToN8);
  } else if (firstroundballpos == 'e') {
    executemovement(StartToN9);
  } else if (firstroundballpos == 'f') {
    executemovement(StartToN10);
  }

  //deliver ball to N4

  if (currentpos == 'a') {
    executemovement(N3ToN4);
  } else if ( currentpos == 'b') {
    executemovement(N5ToN4);
  } else if ( currentpos == 'c') {
    executemovement(N6ToN4);
  } else if ( currentpos == 'd') {
    executemovement(N8ToN4);
  } else if (currentpos == 'e') {
    executemovement(N9ToN4);
  } else if (currentpos == 'f') {
    executemovement(N10ToN4);
  }

  //deliver ball to Alu or Plastic Container
  if (material == 'A') {
    executemovement(N4ToAlu);
    executemovement(AluToEnd);
  } else if (material == 'P') {
    executemovement(N4ToPlastic);
    executemovement(PlasticToEnd);
  }

  inchtravel(4, 120);

}

void executesecondroundpath() {
  currentpos = 's' ; isballfound = 0; material = 'n'; bool allposcovered = 0;
  inchtravelnostop(4, 140); // clear start box
  for (int p = 0; p <= 6 ; p++) {
    while (isballfound == 0) {//traverse pois till ball is found
      if (currentpos == 's') {
        executemovement(StartToN3); //default movement from start
      } else if (currentpos == 'a') {
        executemovement(N3ToN5);
      } else if ( currentpos == 'b') {
        executemovement(N5ToN6);
      } else if ( currentpos == 'c') {
        executemovement(N6ToN8);
      } else if ( currentpos == 'd') {
        executemovement(N8ToN9);
      } else if (currentpos == 'e'){
        executemovement(N9ToN10);
      }else if (currentpos == 'f'){
        executemovement(N10ToN4);
        executemovement(N4ToEnd);
      }
    }
    isballfound = 0;
    deliveryandreturn();


  }

  PointsOfInterest[poinum] = 'E';
  inchtravel(5, 120);
}


void deliveryandreturn() {
  if (currentpos == 'a') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N3ToN4);
  } else if ( currentpos == 'b') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N5ToN4);
  } else if ( currentpos == 'c') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N6ToN4);
  } else if ( currentpos == 'd') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N8ToN4);
  } else if (currentpos == 'e') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N9ToN4);
  } else if (currentpos == 'f') {
    previouspos = currentpos;
    PointsOfInterest[poinum] = currentpos;
    poinum++;
    executemovement(N10ToN4);
  }

  //deliver ball to Alu or Plastic Container ,end if last pos was f
  if (material == 'A') {
    executemovement(N4ToAlu);
    if (previouspos == 'f') {
      executemovement(AluToEnd);
    } else {
      executemovement(AluToN4);
    }
    executemovement(AluToN4);
  } else if (material == 'P') {
    executemovement(N4ToPlastic);
    if (previouspos == 'f') {
      executemovement(PlasticToEnd);
    } else {
      executemovement(PlasticToN4);
    }
  }

  if (previouspos == 'a') {
    executemovement(N4ToN5);
  } else if ( previouspos == 'b') {
    executemovement(N4ToN6);
  } else if ( previouspos == 'c') {
    executemovement(N4ToN8);
  } else if ( previouspos == 'd') {
    executemovement(N4ToN9);
  } else if (previouspos == 'e') {
    executemovement(N4ToN10);
  }
}

//remember to add e at end
void secondroundquickfinish(char path[20]){
  int i =0;
  while(path[i] !='E' ) {
    
  }
}
