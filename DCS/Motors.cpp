#include "Arduino.h"

uint16_t motor[4];
uint8_t PWM_PIN[4] = {2, 5, 3, 4};  //for a quad+: rear,right,left,front


void writeMotors() {      
  uint16_t value; 
  for (int i=0; i<4; i++){
    value = motor[i]-1000;
    // if(i==1){
    //   abs(value);
    // }
    analogWrite(PWM_PIN[i], value/4);
    // Debug motor PWM values sent to propellers
    Serial.println(value/4);
  }
}

void initMotors() {
  for (int i=0; i<4; i++) {
    motor[i] = 1000;
    pinMode(PWM_PIN[i],OUTPUT);
    analogWrite(PWM_PIN[i], 8000);
  }
  writeMotors();
}


