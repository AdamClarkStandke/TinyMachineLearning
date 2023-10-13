#include <ArduinoBLE.h>
#include <Arduino.h>
// Left Controller Pin Congfig
#define ANALOG_X_PIN A2
#define ANALOG_Y_PIN A3
#define ANALOG_BUTTON_PIN A4
#define MAX_THROTTLE 1800
#define MIN_THROTTLE 1000
int bufferStore[3] = {0, 0, 0}; 

struct button {
  byte pressed = 0;
};
 
struct analog {
  short x, y;
  struct button button;
};

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP);
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
  analog leftController;
  analog rightController;
  while (peripheral.connected()) {
      bufferStore[0] = smooth(readAnalogAxisLevel(ANALOG_X_PIN));
      bufferStore[1] = smooth(readAnalogAxisLevel(ANALOG_Y_PIN));
      bufferStore[2] = isAnalogButtonPressed(ANALOG_BUTTON_PIN);
      // // Increase or decrease throttle based on joystick postion
      // if (jThrottle >= 1550 && throttle < MAX_THROTTLE)
      // throttle += 15;
      // if (jThrottle <= 1450 && throttle > 1000)
      // throttle -= 15; 
      gestureCharacteristic.writeValue(bufferStore, 6);
  }
  Serial.println("- Peripheral device disconnected!");
}

// Helper Functions
int readAnalogAxisLevel(int pin){
  return map(analogRead(pin), 0, 1023, 1000, 2000);
}
 
bool isAnalogButtonPressed(int pin){
  return digitalRead(pin)==LOW;
}

// To compensate for inaccuracy and fluctuations in readings around mid value
int smooth(int value){
  if (value < 1525 && value > 1475)
    value = 1500;
  return value;
}



