#include "Arduino.h"

uint16_t motor[4];
uint8_t PWM_PIN[4] = {2, 5, 3, 4};  //for a quad+: rear,right,left,front


void writeMotors() {      
  for (int i=0; i<4; i++)
    analogWrite(PWM_PIN[i], (motor[i]-1000)/4);
}

void initMotors() {
  for (int i=0; i<4; i++) {
    motor[i] = 1000;
    pinMode(PWM_PIN[i],OUTPUT);
    analogWrite(PWM_PIN[i], 8000);
  }
  writeMotors();
}


