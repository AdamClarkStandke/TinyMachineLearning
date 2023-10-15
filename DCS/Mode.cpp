#include "Arduino.h"
#include "Config.h"
#include "BLE_RX.h"

extern uint16_t rcValue[];
extern float IMURoll,IMUPitch,IMUHead;

float rcRate[4] = {1.00f, 1.0f, 1.0f, 3.0f};
float maxAngle = 55.0f;
float prevHead = 0.0f;
float axisCmd[4] = {0.0f, 0.0f, 0.0f, 0.0f};  //output

enum FlightModes {MODE_MANUAL, MODE_STABILIZE};
enum FlightModes mode = MODE_STABILIZE;

float circleDiff(float a1, float a2)
{
  float diff = a1 - a2;
  if (diff >  180.0f) diff -= 360.0f;
  if (diff < -180.0f) diff += 360.0f;
  return diff;
}

const float yawRateSmooth  = 0.99f;
float prevYawRate = 0.0f;
void doMode() {

  // apply throttle
  // todo: throttleMid, exp
  axisCmd[0] = (constrain(rcValue[0], MINRC, MAXRC) - MINRC)*1.67f;

  // Debug throttle axis command 
  // Serial.println(axisCmd[0]);

  float halfRange = (float)(MIDRC - MINRC);
  switch (mode)
  {
  case  (MODE_MANUAL):
    // axis cmd = rc input
    axisCmd[1] = rcRate[1] * (float)((int16_t)rcValue[1] - (int16_t)MIDRC) / halfRange;
    axisCmd[2] = rcRate[2] * (float)((int16_t)rcValue[2] - (int16_t)MIDRC) / halfRange;
    axisCmd[3] = rcRate[3] * (float)((int16_t)rcValue[3] - (int16_t)MIDRC) / halfRange;
    break;
  case (MODE_STABILIZE):
    // compute and smooth the yaw rate
    float yawRate = deltat_inv * circleDiff(IMUHead, prevHead);
    yawRate = ((1.0f-yawRateSmooth) * yawRate) + (yawRateSmooth * prevYawRate);
    prevYawRate = yawRate;
    
    // pitch/roll: axis cmd = imu angle - rc angle
    axisCmd[1] = -((float)IMURoll  - maxAngle * rcRate[1] * (float)((int16_t)rcValue[1] - (int16_t)MIDRC) / halfRange) / 90.0f;
    axisCmd[2] = -((float)IMUPitch - maxAngle * rcRate[2] * (float)((int16_t)rcValue[2] - (int16_t)MIDRC) / halfRange) / 90.0f;
    
    // Debug roll axis command i.e.  IMURoll  - rc angle
    // Serial.println(axisCmd[1]);
    // Debug pitch axis command i.e. IMUPitch - rc angle 
    // Serial.println(axisCmd[2]);

    // yaw: axis cmd = imu rate - rc rate
    axisCmd[3] =  (yawRate- 90.0f* rcRate[3] * (float)((int16_t)rcValue[3] - (int16_t)MIDRC) / halfRange) / 90.0f;
    prevHead = IMUHead;

    // Debug yaw axis command i.e.  IMUHead - rc angle
    // Serial.println(axisCmd[3]);
    
  }
}

