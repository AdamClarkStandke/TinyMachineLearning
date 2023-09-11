#include "Config.h"
#include "RX.h"
#include "BLE_IMU.h"
#include "Motors.h"
#include "MSP.h"
#include "Debug.h"

extern volatile uint16_t rcValue[];

int16_t fastLoopTiming, slowLoopTiming;

//void doMode();
//void doPID();
//void doMix();

void setup() {
    //initMSP();
    //initRX();
    initIMU();  // (have to implement my IMU system for nano BLE)
    //initMotors();
}

unsigned long fastLoopLength;
unsigned long fastLoopStart = 0;
unsigned long slowLoopLength;
unsigned long slowLoopStart = 0;
void loop() {
  // the fast loop for flight control
  unsigned long fastLoopEnd = micros();
  fastLoopLength = fastLoopEnd - fastLoopStart;
  if ((fastLoopLength) > FASTLOOPTARGET)
  {
    fastLoopStart = fastLoopEnd;
    //readIMU();        // read raw gyro/accel/mag (have to implement my IMU system for nano BLE)
    calcIMU();        // calculate current yaw/pitch/roll
    //doMode();         // calculate yaw/pitch/roll commands
    //doPID();          // smooth yaw/pitch/roll commands
    //doMix();          // converts cmds to motor speeds
    //writeMotors();    // write to pwm
    //mspRead();        // check for new msp msgs
    fastLoopTiming = micros() - fastLoopEnd;
  }
  
  //  the slow loop for communications
  unsigned long slowLoopEnd = millis();
  slowLoopLength = slowLoopEnd - slowLoopStart;
  if ((slowLoopLength) > SLOWLOOPTARGET)
  {
    slowLoopStart = slowLoopEnd;
    long slowLoopTimingStart = micros();

    //debugVals[0] = fastLoopTiming;
    //debugVals[1] = slowLoopTiming;
    //mspWrite();
    slowLoopTiming = micros() - slowLoopTimingStart;
  }

}


