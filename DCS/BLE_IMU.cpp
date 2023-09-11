#include <MahonyAHRS.h>
#include "BLE_IMU.h"
#include <Wire.h>

float IMURoll,IMUPitch,IMUHead;        // cooked IMU data
float Acc[3], Gyro[3], Mag[3];         // raw IMU data
MyBoschSensor myIMU(Wire1);

void read_data() {
  if (myIMU.accelerationAvailable()){
    myIMU.readAcceleration(Acc[0], Acc[1], Acc[2]);
  }
  if (myIMU.gyroscopeAvailable()){
    myIMU.readGyroscope(Gyro[0], Gyro[1], Gyro[2]);
  }
  if (myIMU.magneticFieldAvailable()){
     myIMU.readMagneticField(Mag[0], Mag[1], Mag[2]);
  }
}

void initIMU(){
  Serial.begin(115200);
  while (!Serial);
  myIMU.debug(Serial);
  //callback function to read data from
  myIMU.onInterrupt(read_data);
  myIMU.begin();
}

void calcIMU(){

Serial.print("accel: \t");
Serial.print(Acc[0]);
Serial.print('\t');
Serial.print(Acc[1]);
Serial.print('\t');
Serial.print(Acc[2]);
Serial.println();
}

