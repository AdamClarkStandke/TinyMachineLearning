/*

  BLE_Peripheral_MotorController.ino


  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE 
  Sense as a peripheral device and specifies a service and a characteristic. Depending 
  of the value of the specified characteristic, controls the Drone's motors. 
  The circuit:

  - Arduino Nano 33 BLE Sense.
  - DC Motors
  - MOSFET NPN transistor

  This example code is in the public domain.
  

*/


#include <ArduinoBLE.h>

      
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";

const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


const int motor1pin = 11;       // pin for motor 1
// const int ramp_delay = 40;      // loop delay time for motor ramp up in milliseconds

int gesture = 0;


BLEService gestureService(deviceServiceUuid); 

BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);



void setup() {

  Serial.begin(9600);


  if (!BLE.begin()) {

    Serial.println("- Starting Bluetooth® Low Energy module failed!");

    while (1);

  }


  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");

  BLE.setAdvertisedService(gestureService);

  gestureService.addCharacteristic(gestureCharacteristic);

  BLE.addService(gestureService);

  gestureCharacteristic.writeValue(-1);

  BLE.advertise();


  Serial.println("Nano 33 BLE (Peripheral Device)");

//   Serial.println(" ");
//   int speed = 0; // ramp up slowly to default speed
//   while(speed<defaultSpeed){
//      // write PWM values to motor pins
//      analogWrite(motor1pin,speed);
// //     analogWrite(motor2pin,speed);
// //     analogWrite(motor3pin,speed);
// //     analogWrite(motor4pin,speed); 
//      speed++;            // increment speed
//      delay(ramp_delay);  // short delay
//   }

}


void loop() {

  BLEDevice central = BLE.central();

  Serial.println("- Discovering central device...");

  delay(500);


  if (central) {

    Serial.println("* Connected to central device!");

    Serial.print("* Device MAC address: ");

    Serial.println(central.address());

    Serial.println(" ");


    while (central.connected()) {

      if (gestureCharacteristic.written()) {

         gesture = gestureCharacteristic.value();

         writeGesture(gesture);

       }

    }

    

    Serial.println("* Disconnected to central device!");

  }

}


void writeGesture(int gesture) {

  if(gesture>255){gesture=255;}
  if(gesture<0){gesture=0;} 
  // send PWM signal motor1pin
  analogWrite(motor1pin,gesture);
  Serial.print("* Actual value: ");
  Serial.println(gesture);

}

