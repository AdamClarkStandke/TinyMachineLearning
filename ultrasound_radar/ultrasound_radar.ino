#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
int16_t AccX, AccY, AccZ;
int16_t GyroX, GyroY, GyroZ;
int16_t accAngleX, accAngleY, accAngleZ, gyroAngleX, gyroAngleY, gyroAngleZ;
int16_t roll, pitch, yaw;
int16_t elapsedTime, currentTime, previousTime;
const int numReadings = 1;   // set a variable for the number of readings to take
int index = 0;                // the index of the current reading
int total = 0;                // the total of all readings
int average = 0;              // the average
int echoPin = 6;              // the SRF05's echo pin
int initPin = 7;              // the SRF05's init pin
unsigned long pulseTime = 0;  // variable for reading the pulse
unsigned long distance = 0;   // variable for storing distance






void setup() {
  pinMode(initPin, OUTPUT);
  // make the echo pin an input:
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Wire.begin(); 
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  // // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  // Wire.beginTransmission(MPU);
  // Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  // Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  // Wire.endTransmission(true);
  delay(20);                    
}

void loop() {
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  
  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI); 
  accAngleY = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI); 
  accAngleZ = (atan(sqrt(pow(AccX, 2)+ pow(AccY, 2))/ AccZ)* 180 / PI);
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
 
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  // Correct the outputs with the calculated error values
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
  gyroAngleZ =  gyroAngleZ + GyroZ* elapsedTime;    
  yaw = (0.9 * gyroAngleZ + 0.1 * accAngleZ);      //fixing yaw drift of Gyro
  Wire.endTransmission(true);

  digitalWrite(initPin, LOW);
  digitalWrite(initPin, HIGH);                           // send signal
  digitalWrite(initPin, LOW);                            // close signal
  pulseTime = pulseIn(echoPin, HIGH);                    // calculate time for signal to return
  distance = pulseTime / 58;                             // convert to centimetres
  total = total + distance;                              // update total                           

  String yaw_one = String(yaw);
  String pul_one = String(total);
  Serial.println(yaw_one+"V"+pul_one);                             
}
