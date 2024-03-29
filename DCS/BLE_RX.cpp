#include <ArduinoBLE.h>
#include "BLE_RX.h"
#include <Arduino.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


int rcValue[4] = {0, 0, 0, 0}; 

BLEService gestureService(deviceServiceUuid); 
BLECharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite | BLENotify, sizeof(rcValue));

void writeGesture(BLEDevice central, BLECharacteristic characteristic) {
  if (central) {

    // Debug Bluetooth communication connection to central device
      if (characteristic.written()) {
        int x = characteristic.readValue(rcValue, sizeof(rcValue));
        for (int i=0; i<4; i++){
          rcValue[i] = abs(constrain(rcValue[i], MINRC, MAXRC));
        } 

    }
  }
}

void initBLErx() {
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
  // Debug Bluetooth Communication i.e. init peripheral device
  // Serial.println("Connected to the Nano 33 BLE (Peripheral Device)");
  // Serial.println(" "); 
}




