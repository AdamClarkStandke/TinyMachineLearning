/* 
Most of this code comes from dhir_33 when posted
in the arduino forum https://forum.arduino.cc/t/spikes-when-using-mahony-filter/1106933
In this case, I am not using adafruit's ahrs library but rather
the Mahony AHRS filter as maintained by PaulStoffregen and njh as found here:
https://github.com/PaulStoffregen/MahonyAHRS
*/
#include <MahonyAHRS.h>
#include "BLE_IMU.h"
#include <Wire.h>
#include "Config.h"

float IMURoll,IMUPitch,IMUHead;        // cooked IMU data
float Acc[3], Gyro[3], Mag[3];         // raw IMU data
float   throttleCorrection;
Mahony filter;
MyBoschSensor myIMU(Wire);
//float gyroDriftX, gyroDriftY, gyroDriftZ;  // units dps

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

// void calibrateIMU(int delayMillis, int calibrationMillis) {
//   int calibrationCount = 0;
//   delay(delayMillis);  // to avoid shakes after pressing reset button
//   float sumX, sumY, sumZ;
//   int startTime = millis();
//   while (millis() < startTime + calibrationMillis) {
//     read_data();
//     // in an ideal world gyroX/Y/Z == 0, anything higher or lower represents drift
//     sumX += gyroX;
//     sumY += gyroY;
//     sumZ += gyroZ;
//     calibrationCount++;
//   }

//   if (calibrationCount == 0) {
//     Serial.println("Failed to calibrate");
//   }

//   gyroDriftX = sumX / calibrationCount;
//   gyroDriftY = sumY / calibrationCount;
//   gyroDriftZ = sumZ / calibrationCount;
// }

void initIMU(){
  //callback function to read data from
  myIMU.onInterrupt(read_data);
  myIMU.begin();
  //calibrateIMU(250, 250);
  filter.begin(1000); // filter to expect 100 measurements per second
}

void calcIMU(){
  // BMI270 gyroscope uses degrees/second
  // Mahony expects gyroscope in radians/second
  float gyroScale = 3.14159f / 180.0f;
  Gyro[0] =  Gyro[0] * gyroScale;
  Gyro[1] =  Gyro[1] * gyroScale;
  Gyro[2] =  Gyro[2] * gyroScale;
  filter.update(Gyro[0],Gyro[1],Gyro[2], Acc[0], Acc[1], Acc[2], Mag[0], Mag[1], Mag[2]);
  IMURoll = filter.getRoll();
  IMUPitch = filter.getPitch();
  IMUHead = filter.getYaw();

  // Debug IMU values
  Serial.print("IMURoll:");
  Serial.println(IMURoll);
  delay(20);
  Serial.print("IMUPitch:");
  Serial.println(IMUPitch);
  delay(20);
  //Serial.print("IMUHead:");
  //Serial.println(IMUHead);
}

