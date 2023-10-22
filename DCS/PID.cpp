#include "Arduino.h"
#include "Config.h"

extern float axisCmd[];

#define MYPIDITEMS 4
float axisCmdPID[MYPIDITEMS] = { 0.0f, 0.0f, 0.0f, 0.0f };
float pid_p[MYPIDITEMS] = { 0.5f, 0.5f,   0.5f,   0.5f }; // 4p & 0.5d yaw
float pid_i[MYPIDITEMS] = { 0.0f, 0.0f,  0.0f,  0.0f };
float pid_d[MYPIDITEMS] = { 0.0f, 0.0f,   0.0f,   0.0f };
uint16_t tpaCutoff = 500;
float tpaMult = 1.25f;

float prevE[MYPIDITEMS] = { 0, 0, 0, 0 };
float pid_isum[MYPIDITEMS] = { 0, 0, 0, 0 };
float pid_ddt[MYPIDITEMS] = { 0, 0, 0, 0 };
float maxDDT[MYPIDITEMS] = { 0, 0, 0, 0 };
float minDDT[MYPIDITEMS] = { 0, 0, 0, 0 };
void doPID() {
  float e;
  float tpa = (axisCmd[0] < tpaCutoff) ? ((tpaMult - 1.0f) * ((float)(tpaCutoff - axisCmd[0]) / (float)(tpaCutoff))) + 1.0f : 1.0f;
  for (int i=0; i<MYPIDITEMS; i++)
  {
    e = axisCmd[i];
    pid_isum[i] = constrain(pid_isum[i] + (e), -0.1f, 0.1f); // constrain to stop windup
    pid_ddt[i] = (e - prevE[i]) / deltat;
    if (pid_ddt[i] < minDDT[i]) minDDT[i] = pid_ddt[i];
    if (pid_ddt[i] > maxDDT[i]) maxDDT[i] = pid_ddt[i];
    //if ((i==1) || (i==2)) // tpa on roll and pitch only
    //  axisCmdPID[i] = (tpa * pid_p[i] * e) + (pid_i[i] * pid_isum[i]) + (tpa * pid_d[i] * pid_ddt[i]);
    //else
      axisCmdPID[i] = (pid_p[i] * e) + (pid_i[i] * pid_isum[i]) + (pid_d[i] * pid_ddt[i]);
    prevE[i] = e;
  }
}


