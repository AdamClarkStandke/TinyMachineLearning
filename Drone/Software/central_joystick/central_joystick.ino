/*

  BLE_Drone_Controller


  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE
  as a central device and looks for a specified service and characteristic in a
  peripheral device. If the specified service and characteristic is found in a
  peripheral device, the x and y coordiantes of the joystick are mapped to PWM
  values to control the drone's motors, and is written to the specified characteristic.

  The circuit:

  - Arduino Nano 33 BLE
  - 1pc Joystick Dual Axis XY PS2 Module for Arduino
  
  This example code is in the public domain.
  modifications by Adam Clark Standke, 
  $BleCommunications:orginal author unkown
  $Drone/Joystick mechanics taken from Ben Finio:https://www.sciencebuddies.org/stem-activities/drone-arduino-steering-joystick
  $Joystick mechanics taken from Tom Igoe in his program JoystickMouseControl:https://www.arduino.cc/en/Tutorial/BuiltInExamples/JoystickMouseControl
*/


#include <ArduinoBLE.h>

// constants for pins switch; converion constants a and b; defaultSpeed and speed change
const int switchPin = 2;    // switch to turn on and off mouse control
const float a = 0.3;            // constant for converting analog voltages to PWM values
const float b = 1.5;            // offset for converting voltages to PWM values
const int defaultSpeed = 130;   // default PWM value
const int speedChange = 90;     // PWM value to add or subtract

// motor speed variable:
int motor1speed = defaultSpeed;      // motor 1 PWM value between 0-255

// device service id and characteristic id
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";



void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  BLE.setLocalName("Joystic Controller");
  BLE.advertise();
  Serial.println("Joystic Controller");
  Serial.println(" ");
}


void loop() {

  connectToPeripheral();

}


void connectToPeripheral() {

  BLEDevice peripheral;
  Serial.println("- Discovering peripheral device...");
  do
  {
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();

  } while (!peripheral);
  if (peripheral) {
    Serial.println("* Peripheral device found!");
    Serial.print("* Device MAC address: ");
    Serial.println(peripheral.address());
    Serial.print("* Device name: ");
    Serial.println(peripheral.localName());
    Serial.print("* Advertised service UUID: ");
    Serial.println(peripheral.advertisedServiceUuid());
    Serial.println(" ");
    BLE.stopScan();
    controlPeripheral(peripheral);
  }

}


void controlPeripheral(BLEDevice peripheral) {

  Serial.println("- Connecting to peripheral device...");
  if (peripheral.connect()) {
    Serial.println("* Connected to peripheral device!");
    Serial.println(" ");
  } else {
    Serial.println("* Connection to peripheral device failed!");
    Serial.println(" ");
    return;
  }
  Serial.println("- Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("* Peripheral device attributes discovered!");
    Serial.println(" ");
  } else {
    Serial.println("* Peripheral device attributes discovery failed!");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }


  BLECharacteristic gestureCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);


  if (!gestureCharacteristic) {
    Serial.println("* Peripheral device does not have joystick characteristic!");
    peripheral.disconnect();
    return;

  } 
  else if (!gestureCharacteristic.canWrite()) {
    Serial.println("* Peripheral does not have a writable characteristic!");
    peripheral.disconnect();
    return;
  }
  // sending joystick movement over BLE to peripheral device
  while (peripheral.connected()) {

    // read and scale the two axes:
    int xReading = readAxis(A0);
    int yReading = readAxis(A1);
    // convert analog voltages to motor speed for motor 1
    motor1speed = defaultSpeed+speedChange*(a*yReading-a*xReading);
    Serial.print("* Writing value to gesture_type characteristic: ");
    Serial.println(motor1speed);
    // sending motor1speed over BLE to sense 
    gestureCharacteristic.writeValue((byte)motor1speed);
    Serial.println("* Writing motor1speed to gesture_type characteristic done!");
    Serial.println(" ");
  }
  Serial.println("- Peripheral device disconnected!");
}


int readAxis(int axis) {
  // read the analog input:
  int reading = analogRead(axis);
  // map the reading from the analog input range to the output range:
  //Serial.println(reading);
  //reading = 5*reading/1023;          // convert to a voltage from 0-5V
  reading = abs(reading) % 255;
  return reading;
}
