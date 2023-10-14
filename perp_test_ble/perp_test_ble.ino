#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


extern int rcValue[3] = {0, 0, 0}; 

BLEService gestureService(deviceServiceUuid); 
BLECharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite | BLENotify, 6);


void setup() {
  Serial.begin(9600);
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  // assign event handlers for characteristic
  gestureCharacteristic.setEventHandler(BLEWritten, writeGesture);
  BLE.addService(gestureService);
  BLE.advertise();
  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}


void loop() {
  BLE.poll();
}


void writeGesture(BLEDevice central, BLECharacteristic characteristic) {
  //Serial.println("- Discovering central device...");
  if (central) {
    // Serial.println("* Connected to central device!");
    // Serial.print("* Device MAC address: ");
    // Serial.println(central.address());
    // Serial.println(" ");
      if (characteristic.written()) {
        int x = characteristic.readValue(rcValue, 6);
        Serial.println(rcValue[0]);
        Serial.println(rcValue[1]);
        Serial.println(rcValue[2]);
       }
  }
}
