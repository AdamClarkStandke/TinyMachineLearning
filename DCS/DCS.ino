#include "Config.h"
#include "BLE_IMU.h"
#include "Motors.h"
#include <ArduinoBLE.h>
#include "BLE_RX.h"
#include "Mode.h"
#include "Mix.h"
#include "PID.h"

extern uint16_t rcValue[];
int16_t fastLoopTiming, slowLoopTiming;

void setup() {
    Serial.begin(9600);
    initBLErx();
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
    BLE.poll();       // poll bluetooth for new Joystick values
    calcIMU();        // calculate current yaw/pitch/roll from IMU
    doMode();         // calculate yaw/pitch/roll axis commands
    doPID();          // smooth yaw/pitch/roll commands
    doMix();          // converts axis cmds to motor speeds
    writeMotors();    // write to pwm
    fastLoopTiming = micros() - fastLoopEnd;
  }
  
  // //  the slow loop for communications
  // unsigned long slowLoopEnd = millis();
  // slowLoopLength = slowLoopEnd - slowLoopStart;
  // if ((slowLoopLength) > SLOWLOOPTARGET)
  // {
  //   slowLoopStart = slowLoopEnd;
  //   long slowLoopTimingStart = micros();
  //   slowLoopTiming = micros() - slowLoopTimingStart;
  // }

}


