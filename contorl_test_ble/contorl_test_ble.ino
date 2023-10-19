#include <ArduinoBLE.h>
#include <Arduino.h>
// Left Controller Pin Congfig
#define ANALOG_X_PIN A4
#define ANALOG_Y_PIN A5
// Right Controller Pin Congfig
#define ANALOG_X1_PIN A2
#define ANALOG_Y1_PIN A3
#define MAX_THROTTLE 1800
int bufferStore[4] = {0, 0, 0, 0}; 
int input3Pin = 3;
int input2Pin = 2;
int throttle = 1000;

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

void setup() {
  Serial.begin(9600);
  pinMode(input3Pin, INPUT);
  pinMode(input2Pin, INPUT);
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
      if (digitalRead(input3Pin) == HIGH){
      // Send sequence to start the drone motors
      throttle = 1000;
      bufferStore[0] = 1000; 
      bufferStore[1] = 1000; 
      bufferStore[2] = 1500; 
      bufferStore[3] = 1500; 
      gestureCharacteristic.writeValue(bufferStore, 8);
      delay(250);
      gestureCharacteristic.writeValue(bufferStore, 8);
      delay(250);
      }
      // if (digitalRead(input2Pin) == HIGH){
      // // Send end sequence to stop the drone motors
      // throttle = 1000;
      // sendPacket(1000, 2000, 1500, 1500);
      // delay(250);
      // sendPacket(1000, 1500, 1500, 1500);
      // delay(250);
      // }
      delay(10);
      // reading throttle
      bufferStore[0] = readAnalogAxisLevel(smoothOne(analogRead(ANALOG_X_PIN)));
      // reading yaw
      delay(10);
      bufferStore[1] = readAnalogAxisLevel(smoothTwo(analogRead(ANALOG_Y_PIN)));
      delay(10);
      // reading pitch joystick  values (will be done on the right joystick) up=decrease pitch down=increase pitch 
      bufferStore[2] = readAnalogAxisLevel(smoothOne(analogRead(ANALOG_X1_PIN)));
      // reading roll joystick values (will be done on the right joystick) left=decrease roll right=increase roll
      delay(10);
      bufferStore[3] = readAnalogAxisLevel(smoothTwo(analogRead(ANALOG_Y1_PIN)));
      // Increase or decrease throttle based on joystick postion
      if (bufferStore[0] >= 1550 && throttle < MAX_THROTTLE)
        throttle += 15;
      if (bufferStore[0] <= 1450 && throttle > 1000)
        throttle -= 15; 
      bufferStore[0] = throttle; 
      Serial.println(bufferStore[0]);
      Serial.println(bufferStore[1]);
      Serial.println(bufferStore[2]);
      Serial.println(bufferStore[3]);
      gestureCharacteristic.writeValue(bufferStore, 8);
  }
  Serial.println("- Peripheral device disconnected!");
}

// Helper Functions
int readAnalogAxisLevel(int pin){
  return map(pin, 0, 1023, 1000, 2000);
}
 
bool isAnalogButtonPressed(pin_size_t pin){
  return digitalRead(pin);
}

// To compensate for inaccuracy and fluctuations in readings around mid value of joystick (i.e. when not touching it)
int smoothOne(int value){
  if ((value < 580  && value > 564))
    value = 500;
  return value;
}

int smoothTwo(int value){
  if (value == 1023)
    value = 600;
  return value;
}



