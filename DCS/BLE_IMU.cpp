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
// MyBoschSensor myIMU(Wire);


void read_data() {
  if (IMU.accelerationAvailable()){
    IMU.readAcceleration(data.ax, data.ay, data.az);
  }
  if (IMU.gyroscopeAvailable()){
    IMU.readGyroscope(data.gx, data.gy, data.gz);
  }
  if (IMU.magneticFieldAvailable()){
    IMU.readMagneticField(data.mx, data.my, data.mz);
  }
}


void initIMU(){
  // ToDo: see why interrupt is not working
  // myIMU.onInterrupt(read_data);
  IMU.begin();
  ahrs.begin();
  ahrs.setFusionAlgorithm(SensorFusion::MAHONY);
  ahrs.setDeclination(-13.11);                      // Harrisburg, Pennsylvania
}

void calcIMU(){
  
  read_data(); // get raw data
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

  ahrs.setData(data);
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

