#include <MahonyAHRS.h>
#include "BLE_IMU.h"
#include <Wire.h>
#include "MSP.h"
#include "Config.h"

float IMURoll,IMUPitch,IMUHead;        // cooked IMU data
float Acc[3], Gyro[3], Mag[3];         // raw IMU data
float   throttleCorrection;
Mahony filter;
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
  //callback function to read data from
  myIMU.onInterrupt(read_data);
  myIMU.begin();
  filter.begin(100); // filter to expect 100 measurements per second
}

void calcIMU(){

  // TODO: calibrate the Bosh gyroscope for scaling 
  // Update the Mahony filter, with scaled gyroscope
  float gyroScale = 0.001;  // TODO: the filter updates too fast
  Gyro[0] =  Gyro[0] * gyroScale;
  Gyro[1] =  Gyro[1] * gyroScale;
  Gyro[2] =  Gyro[2] * gyroScale;
  filter.update(Gyro[0],Gyro[1],Gyro[2], Acc[0], Acc[1], Acc[2], Mag[0], Mag[1], Mag[2]);
  IMURoll = filter.getRoll();
  IMUPitch = filter.getPitch();
  IMUHead = filter.getYaw();
}



//---------------------
void writeMSP_ATTITUDE() {
    mspWriteStart(MSP_ATTITUDE);
    mspWriteWord((int16_t)(IMURoll*10));
    mspWriteWord((int16_t)(IMUPitch*10));
    mspWriteWord((int16_t)(IMUHead));
    mspWriteEnd();
}
