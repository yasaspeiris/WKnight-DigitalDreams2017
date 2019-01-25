#define LINE1INCHES 8
#define LINE2INCHES 8

/*===================================================================

          //QTRC Variables

  =====================================================================*/
#include <QTRSensors.h>
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {
  A2, A3, A4, A5, A6, A7, A8, A9
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorRead[NUM_SENSORS];
unsigned int SensorPanelVal = 0;
unsigned int position = 0;


/*===================================================================

          //Sonar Variables

  =====================================================================*/
#include <NewPing.h>

#define MAX_DISTANCE_FRONT 15 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar(45, 43, MAX_DISTANCE_FRONT); // THIS IS WHAT WE'RE USING

int i;
int tmp = 0;
int front = 0;

/*===================================================================

          //Motor Driver Variables

  =====================================================================*/

#define LMOTORSPEED 6 //L PWM Pin
#define RMOTORSPEED 7 // R PWM Pin

#define LMOTORCS A0
#define RMOTORCS A1

#define LMOTOR1 52
#define LMOTOR2 50

#define RMOTOR1 48
#define RMOTOR2 46

#define LMOTORSF 32
#define RMOTORSF 30

#define MOTOREN 44

#define MOTOREN2 42

#define LMOTOR_ENC1 18
#define LMOTOR_ENC2 19

#define RMOTOR_ENC1 2
#define RMOTOR_ENC2 3

/* =============================================

    Encoder Variables

    ============================================
*/
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

Encoder MasterENC(LMOTOR_ENC2, LMOTOR_ENC1);
Encoder SlaveENC(RMOTOR_ENC1, RMOTOR_ENC2);
long totalTicks = 0;

#define ticksperrevolutioncheapmotor 768
#define ticksperrevolution 816
#define ticksperinchcheapo 87 //cheap motor encoder pulses per inch (ZGA-31)
#define ticksperinch 94.45 //pololu motor encoder pulses per inch
#define tickspermm 7.42

int i_motord = 0;
boolean startingfromstop = 1;

int MasterPower = 0;
int SlavePower = 0;
int MaxPower = 0;

int error = 0;
int lasterror = 0;



/*===================================================================

          //Servo Variables

  =====================================================================*/

#include <Servo.h>

Servo grabber, lifter,lifter2;
#define GRABBER_OPEN 70 
#define GRABBER_CLOSE 135

#define LIFTER_DOWN 130
#define LIFTER_UP 20
int servotmp = 0;

/*===================================================================

          //Pretty Lights and Switches

  ===================================================================== */

#define STARTSWITCH 30 //
bool startpressed = 0;
#define MODESW 32
bool modepressed = 0;
#define BLUELED2 34
#define YELLOWLED 26
#define BLUELED1 24


/*===================================================================

          //Node instances

  ===================================================================== */

boolean nodeflag = 0;
char currentpos = 's';
char previouspos;
char firstroundballpos;
#define NODEinstance1 11111000
#define NODEinstance2 11111111
#define NODEinstance3 01111111

/*===================================================================

          //Material Variables

  ===================================================================== */

char material;
boolean isballfound = 0;

/*===================================================================

          // Paths - Don't Mess

  ===================================================================== */
//N4 is goal entrance
//Simple letters denote current end position
//N - TravelToNextNode , L - Left , R- Right , T - TurnAround , E- End Current Path, C - Check and Pickup, D- Drop at Goal, P - Pussy Movement 

// Default Start
char StartToN3[10] = {'G', 'N', 'L', 'P', 'C', 'E', 'a'}; //First POI, Won't change

//First Round Start Paths
char StartToN5[10] = {'G', 'N', 'L', 'N', 'R', 'Q', 'C', 'E', 'b'};
char StartToN6[10] = {'G', 'N', 'L', 'N', 'L', 'Q', 'C', 'E', 'c'};
char StartToN8[10] = {'N', 'L', 'N', 'R', 'P', 'C', 'E', 'd'};
char StartToN9[10] = {'N', 'L', 'N', 'R', 'N', 'L', 'Q', 'C', 'E', 'e'};
char StartToN10[10] = {'N', 'L', 'N', 'R', 'N', 'R', 'Q', 'C', 'E', 'f'};


//Area1Deliver
char N3ToN4[10] = {'T', 'N', 'L', 'N', 'R', 'E', 'g'}; //N3 to N4
char N5ToN4[10] = {'T', 'N', 'L', 'N', 'L', 'N', 'R', 'E', 'g'};
char N6ToN4[10] = {'T', 'N', 'R', 'N', 'L', 'N', 'R', 'E', 'g'};

//Area2Deliver
char N8ToN4[10] = {'T', 'N', 'R', 'N', 'E', 'g'};
char N9ToN4[10] = {'T', 'N', 'R', 'N', 'R', 'N', 'E', 'g'};
char N10ToN4[10] = {'T', 'N', 'L', 'N', 'R', 'N', 'E', 'g'};

//Return to Next POI of Area 1
char N4ToN5[10] = {'L', 'N', 'R', 'N', 'R', 'Q','C', 'E', 'b'};
char N4ToN6[10] = {'L', 'N', 'R', 'N', 'L', 'Q','C', 'E', 'c'};

//Return to Next POI of Area 2
char N4ToN8[10] = {'N', 'L', 'P','C', 'E', 'd'};
char N4ToN9[10] = {'N', 'L', 'N', 'L', 'Q','C', 'E', 'e'};
char N4ToN10[10] = {'N', 'L', 'N', 'R', 'Q','C', 'E', 'f'};

//From N4 to Aluminium
char N4ToAlu[10] = {'G', 'N', 'L', 'D', 'E', 'h'};
//From N4 to Plastic
char N4ToPlastic[10] = {'N', 'L', 'D', 'E', 'i'};

//From Aluminium to N4
char AluToN4[10] = {'T', 'N', 'R', 'G', 'N', 'E', 'g'};
//From Plastic to N4
char PlasticToN4[10] = {'T', 'N', 'R', 'N', 'E', 'g'};

char AluToEnd[10] = {'T', 'N', 'L', 'N', 'L', 'N', 'E', 'z'};
char PlasticToEnd[10] = {'T', 'N', 'L', 'G', 'N', 'L', 'N', 'E', 'z'};
char N4ToEnd[10] = {'G','G','N','L'};

//No Ball
//No ball at N3
char N3ToN5[10] = {'R', 'Q','C', 'E', 'b'};
//No ball at N5
char N5ToN6[10] = {'T', 'G', 'Q','C', 'E', 'c'};
//No ball at N6
char N6ToN8[20] = {'T', 'N', 'R', 'N', 'L', 'N', 'L', 'N', 'L', 'P','C', 'E', 'd'};
//No ball at N8
char N8ToN9[10] = {'L', 'Q','C', 'E', 'e'};
//No ball at N9
char N9ToN10[10] = {'T', 'G', 'Q','C', 'E', 'f'};

char testrun[30] = {'N','L','N','R','P','C','T','N','R','G','N','L','D','T','N','R','G','N','L','N','E','z'};



char PointsOfInterest[10]; //Corresponds to N3,N5,N6,N8,N9 and N10 - n is end
int poinum = 0;
