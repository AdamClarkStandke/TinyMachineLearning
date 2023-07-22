#include <PID_v1_bc.h>
#include "Arduino_BMI270_BMM150.h"
#include <MahonyAHRS.h>

const int BR_MOTOR = 6;       // pin for motor 1
const int FL_MOTOR = 5;       // pin for motor 2
const int FR_MOTOR = 4;        // pin for motor 3
const int BL_MOTOR = 3;        // pin for motor 4
//---------------------------------PID------------------------------------
//Define Variables we'll be connecting to
double rollSetpoint, rollInput, rollOutput;
double pitchSetpoint, pitchInput, pitchOutput; 
int targetSpeed[4];
// orientation/motion vars
float x, y, z; 
int degreesX = 0;
int degreesY = 0;

float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float ypr_cal[3];

//Define the aggressive and conservative Tuning Parameters<br>
double consKp = 1, consKi = 0.05, consKd = 0.25;
PID pitchPID(&rollInput, &rollOutput, &rollSetpoint, consKp, consKi, consKd, DIRECT);
PID rollPID(&pitchInput, &pitchOutput, &pitchSetpoint, consKp, consKi, consKd, DIRECT);

void setup() {
//------------------------------PID----------------------------------
  pitchInput = 0.0;
  rollInput = 0.0;  
  pitchSetpoint = 0.0;
  rollSetpoint = 0.0;
  //turn the PID on
  pitchPID.SetMode(AUTOMATIC);
  rollPID.SetMode(AUTOMATIC);

  pitchPID.SetOutputLimits(-20, 20);
  rollPID.SetOutputLimits(-20, 20);
 
  //-------------------------------------------------------------------

  for (int i = 0; i < 4; i++) {
    targetSpeed[i] = 0;
  } 

  pinMode(FL_MOTOR, OUTPUT);
  pinMode(FR_MOTOR, OUTPUT);
  pinMode(BR_MOTOR, OUTPUT);
  pinMode(BL_MOTOR, OUTPUT);

  
  Serial.begin(9600);  
  Serial.println("Started");
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================
int myReading = 0;
void loop() {
  pitchPID.Compute();
  rollPID.Compute();
  int actSpeed[4];
  








  stabilise (targetSpeed, actSpeed, rollOutput, pitchOutput);
  //    targetSpeed = actSpeed; // should this be here or not
}

void stabilise (int* currSpeed, int* actSpeed, float rollDiff, float pitchDiff) {
  //actual Speed is calculated as follows +- half rollDiff +- half pitchDiff
  actSpeed[0] = (int) currSpeed[0] + (rollDiff / 2) - (pitchDiff / 2);
  actSpeed[1] = (int) currSpeed[1] + (rollDiff / 2) + (pitchDiff / 2);
  actSpeed[2] = (int) currSpeed[2] - (rollDiff / 2) + (pitchDiff / 2);
  actSpeed[3] = (int) currSpeed[3] - (rollDiff / 2) - (pitchDiff / 2);
  for (int i = 0; i < 4; i ++) {
    if (actSpeed[i] < 0) actSpeed[i] = 0;  
  }
}
void runIndividual (int* actSpeed) {
  analogWrite(FL_MOTOR, actSpeed[0]);
  analogWrite(FR_MOTOR, actSpeed[1]);
  analogWrite(BR_MOTOR, actSpeed[2]);
  analogWrite(BL_MOTOR, actSpeed[3]);
}