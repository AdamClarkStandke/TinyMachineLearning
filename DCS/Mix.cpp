#include "Arduino.h"
#include "BLE_RX.h"

extern uint16_t rcValue[];
extern float throttleCorrection;

int16_t motorCmd[4]; // with RC and IMU modifiers
extern uint16_t motor[]; // actual
extern float axisCmdPID[];

void doMix(){
  // set throttle
  for (int i=0; i<4; i++){
    motorCmd[i] = (int16_t)axisCmdPID[0] / throttleCorrection;
  }
  // apply roll
  motorCmd[0] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[1]));
  motorCmd[1] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[1]));
  motorCmd[2] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[1]));
  motorCmd[3] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[1]));
  
  // apply pitch
  motorCmd[0] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[2]));
  motorCmd[1] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[2]));
  motorCmd[2] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[2]));
  motorCmd[3] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[2]));
  
  // apply yaw
  motorCmd[0] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[3]));
  motorCmd[1] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[3]));
  motorCmd[2] += (int16_t)(axisCmdPID[0] * (-axisCmdPID[3]));
  motorCmd[3] += (int16_t)(axisCmdPID[0] * ( axisCmdPID[3]));

  // find max motor value
  int16_t maxMotor = 0;
  for (int i=0; i<4; i++){
    maxMotor = max(motorCmd[i], maxMotor);
  }
  //scale all values if needed
  if (maxMotor > 1000)
  {
    float scale = 1000.0f / (float)maxMotor;
    for (int i=0; i<4; i++){
      motorCmd[i] = (int16_t)(scale * (float)motorCmd[i]);
      
      // Debug scaled motor command values i.e. axis commands
      // Serial.println(motorCmd[i]);
    }
  }
  //write motor commands to  actual motors
  for (int i=0; i<4; i++){
      motor[i] = motorCmd[i] + 1000;
      
      // Debug actual motor values sent to motors
      // Serial.println(motor[i]);
  }
  
}


