#include <ArduinoBLE.h>
#include <Arduino.h>
// Left Controller Pin Congfig
#define ANALOG_X_PIN A2
#define ANALOG_Y_PIN A3
#define ANALOG_BUTTON_PIN A4
// TODO: Right Controller Pin Congfig
// MIN and MAX throttle values
#define MAX_THROTTLE 1800
#define MIN_THROTTLE 1000
// Set the range produced by the joysticks
#define ADC_MIN 0
#define ADC_MAX 26400
BLEDevice peripheral;

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
    }

}


void loop() {
  // Create objects
  analog leftController;
  analog rightController;
  // Read leftController
  leftController.x = readAnalogAxisLevel(ANALOG_X_PIN);
  leftController.y = readAnalogAxisLevel(ANALOG_Y_PIN);
  leftController.button.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN);
  // TODO: Throttle Control
  // Check if need to send start up or shut down sequence
  // // if the button has been pressed pin will go LOW
  // if (leftController.button.pressed == LOW){
  // // Send sequence to start the drone motors
  // throttle = 1000;
  // Replace with BLE: sendPacket(1000, 1000, 1500, 1500);
  //   delay(250);
  // Replace with BLE: sendPacket(1000, 1500, 1500, 1500);
  //   delay(250);
  //   linkComplete = true;
  // }
  // if (leftController.button.pressed == LOW){
  // // Send end sequence to stop the drone motors
  // throttle = 1000;
  // Replace with BLE: sendPacket(1000, 2000, 1500, 1500);
  //   delay(250);
  // Replace with BLE: sendPacket(1000, 1500, 1500, 1500);
  //   delay(250);
  // }
  // TODO: Read right Controller
  Serial.print("X:");
  Serial.println(leftController.x);
  //Serial.print("Y:");
  //Serial.println(leftController.y);
  controlPeripheral(peripheral,leftController, rightController);
}

//--------------------------------------START BLE COMMUNICATION CODE----------------------------------------


void controlPeripheral(BLEDevice peripheral, analog &analogOne, analog &analogTwo) {
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
  BLECharacteristic droneCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);
  if (!droneCharacteristic) {
    Serial.println("* Peripheral device does not have gesture_type characteristic!");
    peripheral.disconnect();
    return;
  } else if (!droneCharacteristic.canWrite()) {
    Serial.println("* Peripheral does not have a writable gesture_type characteristic!");
    peripheral.disconnect();
    return;
  }
  while (peripheral.connected()) {
      Serial.print("Writing out leftController vlaues");
      // writing joystick throttle, pitch, roll yaw to drone rcValue 
      droneCharacteristic.writeValue((byte)analogOne.x);
      Serial.println("* Writing value to gesture_type characteristic done!");
      Serial.println(" ");
  }
}
//--------------------------------------END BLE COMMUNICATION CODE----------------------------------------

// Helper Functions
byte readAnalogAxisLevel(int pin){
  return map(analogRead(pin), ADC_MIN, ADC_MAX, 1000, 2000);
}
 
bool isAnalogButtonPressed(int pin){
  return digitalRead(pin) == 0;
}

// To compensate for inaccuracy and fluctuations in readings around mid value
int smooth(int value){
  if (value < 1525 && value > 1475)
    value = 1500;
  return value;
}

