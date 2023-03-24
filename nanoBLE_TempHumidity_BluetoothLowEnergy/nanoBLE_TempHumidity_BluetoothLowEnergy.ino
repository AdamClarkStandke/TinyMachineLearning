#include <ArduinoBLE.h>
#include <Arduino_HS300x.h>

// defining BLE service and two BLE characteristics
BLEService sensorService("de35afca-0a59-4543-afa4-de487b0cabdd");
BLEStringCharacteristic temperatureSensorLevel("c549bd4b-73c5-4c62-bbe7-329bfdf62d98", BLERead | BLENotify, 15);
BLEStringCharacteristic humiditySensorLevel("3df0d7ea-c27d-473d-956f-0eecccba0054", BLERead | BLENotify, 15);

//last sensor data
float oldTemp = 0; 
float oldHumid = 0; 

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!HS300x.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  if (!BLE.begin()){
    Serial.println("starting BLE failed!");
  }
  // config Bluetooth device
  BLE.setLocalName("WieheißistAdamStandkeZimmer?"); 
  BLE.setAdvertisedService(sensorService); 
  sensorService.addCharacteristic(temperatureSensorLevel);
  sensorService.addCharacteristic(humiditySensorLevel);
  BLE.addService(sensorService);
  // setting temp and humid default values
  temperatureSensorLevel.writeValue(String(oldTemp));
  humiditySensorLevel.writeValue(String(oldHumid));
  // advertising itself to BLE readers
  BLE.advertise(); 
  Serial.println("Bluetooth device active, waiting for client...");
}

void loop() {
  // determing which device/BLE reader has connected my device 
  BLEDevice central = BLE.central(); 
  // if connected print device's mac address 
  if (central){
    Serial.print("Connected to client: "); 
    Serial.println(central.address()); 
    digitalWrite(LED_BUILTIN, HIGH); 
    while (central.connected()){
      // call function that updates the temp and humid
      updateTempHumidLevel(); 
      delay(300);
    }
  }
  digitalWrite(LED_BUILTIN, LOW); 
  Serial.print("Disconnected from client:"); 
  Serial.println(central.address());  
}

void updateTempHumidLevel(){
  // read all the sensor values
  float temperature = HS300x.readTemperature();
  float humidity    = HS300x.readHumidity();
  
  // convert from Celsius to Fahrenheit
  temperature = (temperature*9/5)+32;

  if (temperature != oldTemp){
    temperatureSensorLevel.writeValue(String(temperature));
    oldTemp = temperature;     
  }
  if (humidity != oldHumid) {
    humiditySensorLevel.writeValue(String(oldHumid));
    oldHumid = humidity;     
  }



  
  
}
