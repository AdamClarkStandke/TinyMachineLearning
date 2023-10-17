/* 
Most of this code comes from dhir_33 when posted
in the arduino forum https://forum.arduino.cc/t/spikes-when-using-mahony-filter/1106933
In this case, I am not using adafruit's ahrs library but rather
the Mahony filter as contained in the Reefwing AHRS library as maintained by 
David Such and LazaroFilm as found here: https://github.com/Reefwing-Software/Reefwing-AHRS
*/
#include <ReefwingAHRS.h>
#include "Reefwing_imuTypes.h"
#include "BLE_IMU.h"
#include <Wire.h>
#include "Config.h"

float IMURoll,IMUPitch,IMUHead;        // cooked IMU data
float   throttleCorrection;
ReefwingAHRS ahrs;
SensorData data;                       // raw IMU data
MyBoschSensor myIMU(Wire);


void read_data() {
  if (myIMU.accelerationAvailable()){
    myIMU.readAcceleration(data.ax, data.ay, data.az);
  }
  if (myIMU.gyroscopeAvailable()){
    myIMU.readGyroscope(data.gx, data.gy, data.gz);
  }
  if (myIMU.magneticFieldAvailable()){
    myIMU.readMagneticField(data.mx, data.my, data.mz);
  }
}


void initIMU(){
  //callback function to read data from
  myIMU.onInterrupt(read_data);
  myIMU.begin();
  ahrs.begin();
  ahrs.setFusionAlgorithm(SensorFusion::MAHONY);
  ahrs.setDeclination(-13.11);                      // Harrisburg, Pennsylvania
}

void calcIMU(){
  // BMI270 gyroscope uses degrees/second
  ahrs.setData(data);
  // Debug raw IMU data 
  // Serial.println(data.ax);
  // Serial.println(data.ay);
  // Serial.println(data.az);
  // Serial.println(data.gx);
  // Serial.println(data.gy);
  // Serial.println(data.gz);
  // Serial.println(data.mx);
  // Serial.println(data.my);
  // Serial.println(data.mz);

  ahrs.update();  
  IMURoll = ahrs.angles.roll;
  IMUPitch = ahrs.angles.pitch;
  IMUHead = ahrs.angles.heading;

  // Debug IMU values
  // Serial.print("IMURoll:");
  // Serial.println(IMURoll);
  // Serial.print("IMUPitch:");
  // Serial.println(IMUPitch);
  // Serial.print("IMUHead:");
  // Serial.println(IMUHead);
}

