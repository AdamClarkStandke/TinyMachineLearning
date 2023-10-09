#include <ArduinoBLE.h>
#include <Arduino.h>
#define ANALOG_X_PIN A2
#define ANALOG_Y_PIN A3
#define ANALOG_BUTTON_PIN A4
//Default values when axis not actioned
#define ANALOG_X_CORRECTION 128
#define ANALOG_Y_CORRECTION 128

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
  while (!Serial);
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
  analog analog;
  analog.x = readAnalogAxisLevel(ANALOG_X_PIN) - ANALOG_X_CORRECTION;
  analog.y = readAnalogAxisLevel(ANALOG_Y_PIN) - ANALOG_Y_CORRECTION;
  analog.button.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN);
  Serial.print("X:");
  Serial.println(analog.x);
  Serial.print("Y:");
  Serial.println(analog.y);
  //connectToPeripheral(analog);
}

//--------------------------------------START BLE COMMUNICATION CODE----------------------------------------

void connectToPeripheral(analog &analog){
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
    controlPeripheral(peripheral, analog);
  }
}


void controlPeripheral(BLEDevice peripheral, analog &analog) {
  Serial.println("- Connecting to peripheral device...");
  if (peripheral.connect()) {
    Serial.println("* Connected to peripheral device!");
    Serial.println(" ");
  } 
  else 
  {
    Serial.println("* Connection to peripheral device failed!");
    Serial.println(" ");
    return;
  }
  Serial.println("- Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("* Peripheral device attributes discovered!");
    Serial.println(" ");
  } 
  else 
  {
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
      Serial.print("* Writing value to gesture_type characteristic: ");
      // writing joystick throttle, pitch, roll yaw to drone rcValue 
      gestureCharacteristic.writeValue((byte)analog.x);
      Serial.println("* Writing value to gesture_type characteristic done!");
      Serial.println(" ");
  }
}
//--------------------------------------END BLE COMMUNICATION CODE----------------------------------------

// Helper Functions
byte readAnalogAxisLevel(int pin){
  return map(analogRead(pin), 0, 1023, 0, 255);
}
 
bool isAnalogButtonPressed(int pin){
  return digitalRead(pin) == 0;
}
