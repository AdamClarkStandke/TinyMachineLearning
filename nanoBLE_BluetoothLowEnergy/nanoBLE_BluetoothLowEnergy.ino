#include <ArduinoBLE.h>


void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  if (!BLE.begin()){
  Serial.println("starting BLE failed!");
  while(1);
  }
  BLE.setLocalName("HelloBLE");
  BLE.setAdvertisedServiceUuid("d51b2bb6-9003-4b45-82ed-815c02f9e09c");
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  
  BLEDevice central = BLE.central();
  if (central){
    Serial.print("connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    while (central.connected()){
      // do nothing
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());

  }  
}
