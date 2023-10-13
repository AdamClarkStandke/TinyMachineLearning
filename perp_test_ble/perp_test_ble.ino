#include <ArduinoBLE.h>
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


int gesture = -1;
int rcValue[3] = {0, 0, 0}; 

BLEService gestureService(deviceServiceUuid); 
BLECharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite, 6);

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
  //gestureCharacteristic.writeValue(-1);
  BLE.advertise();
  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
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
        gesture = gestureCharacteristic.readValue(rcValue, 6);
        writeGesture(rcValue[0]);
        writeGesture(rcValue[1]);
        writeGesture(rcValue[2]);
       }
    }
    Serial.println("* Disconnected to central device!");
  }
}


void writeGesture(int gesture) {
  Serial.println(gesture);
}
