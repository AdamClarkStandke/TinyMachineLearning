#include "Config.h"
#include "BLE_IMU.h"
#include "Motors.h"
#include "MSP.h"
#include "Debug.h"

extern volatile uint16_t rcValue[];

int16_t fastLoopTiming, slowLoopTiming;

void doMode();
void doPID();
void doMix();

void setup() {
    Serial.begin(9600);
    initMSP();
    initRX();
    initIMU();  
    initMotors();
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
    calcIMU();        // calculate current yaw/pitch/roll
    Serial.println("IMU CALC Done");
    doMode();         // calculate yaw/pitch/roll commands
    //Serial.println("Mode Done");
    doPID();          // smooth yaw/pitch/roll commands
    //Serial.println("PID Done");
    doMix();          // converts cmds to motor speeds
    //Serial.println("Mixing Done");
    writeMotors();    // write to pwm
    //Serial.println("WritingMotors Done");
    mspRead();        // check for new msp msgs
    //Serial.println("Message Read Done");
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
    mspWrite();
    slowLoopTiming = micros() - slowLoopTimingStart;
  }

}


