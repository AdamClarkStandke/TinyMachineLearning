#include <ArduinoBLE.h>
#include <Arduino.h>
// Left Controller Pin Congfig
#define ANALOG_X_PIN A4
#define ANALOG_Y_PIN A3
#define LEFT_BUTTON 11
// Right Controller Pin Congfig
#define ANALOG_X1_PIN A1
#define ANALOG_Y1_PIN A2
#define RIGHT_BUTTON 12
#define MAX_THROTTLE 1800
int bufferStore[4] = {0, 0, 0, 0}; 
int throttle = 1000;

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  BLE.setLocalName("Nano 33 BLE (Central)"); 
  BLE.advertise();
  Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
  Serial.println(" ");
}

void loop() {
  connectToPeripheral();
}


void connectToPeripheral(){
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
    Serial.println("* Peripheral device does not have gesture_type characteristic!");
    peripheral.disconnect();
    return;

  } else if (!gestureCharacteristic.canWrite()) {
    Serial.println("* Peripheral does not have a writable gesture_type characteristic!");
    peripheral.disconnect();
    return;
  }
  while (peripheral.connected()) {
      // if (digitalRead(LEFT_BUTTON) == LOW){
      // // Send sequence to start the drone motors
      // throttle = 1000;
      // bufferStore[0] = 1000; 
      // bufferStore[1] = 1000; 
      // bufferStore[2] = 1500; 
      // bufferStore[3] = 1500; 
      // gestureCharacteristic.writeValue(bufferStore, 8);
      // delay(250);
      // gestureCharacteristic.writeValue(bufferStore, 8);
      // delay(250);
      // }
      // if (digitalRead(RIGHT_BUTTON) == LOW){
      // // Send end sequence to stop the drone motors
      // throttle = 1000;
      // bufferStore[0] = 1000; 
      // bufferStore[1] = 2000; 
      // bufferStore[2] = 1500; 
      // bufferStore[3] = 1500; 
      // gestureCharacteristic.writeValue(bufferStore, 8);
      // delay(250);
      // gestureCharacteristic.writeValue(bufferStore, 8);
      // delay(250);
      // }
      // reading throttle from left joystick (i.e. y-axis)
      bufferStore[0] = readAnalogAxisLevel(analogRead(ANALOG_Y_PIN));
      // reading roll from right joystick (i.e. x-axis)
      bufferStore[1] = smooth(readAnalogAxisLevel(analogRead(ANALOG_X1_PIN)));
      // reading pitch  from right joystick (i.e. y-axis)
      bufferStore[2] = smooth(readAnalogAxisLevel(analogRead(ANALOG_Y1_PIN)));
      // reading yaw from left joystick (i.e. x-axis)
      bufferStore[3] = smooth(readAnalogAxisLevel(analogRead(ANALOG_X_PIN)));
      // Increase or decrease throttle based on joystick postion
      if (bufferStore[0] >= 1550 && throttle < MAX_THROTTLE)
        throttle += 15;
      if (bufferStore[0] <= 1450 && throttle > 1000)
        throttle -= 15; 
      bufferStore[0] = throttle; 
      gestureCharacteristic.writeValue(bufferStore, sizeof(bufferStore));
  }
  Serial.println("- Peripheral device disconnected!");
}

// Helper Functions
int readAnalogAxisLevel(int pin){
  return map(pin, 0, 1023, 1000, 2000);
}
 
// To compensate for inaccuracy and fluctuations in readings around mid value
int smooth(int value){
  if (value < 1525 && value > 1475)
    value = 1500;
  return value;
}


