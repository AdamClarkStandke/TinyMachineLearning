# TinyMachineLearning

Developing Embedded Applications that for the most part deal with machine learning as detailedfrom the book TinyML Cookbook by Gian Iodice &amp; Ronan Naughton. 

Tiny machine learning is broadly defined as a fast growing field of machine learning technologies and applications including hardware (dedicated integrated circuits), algorithms and software capable of performing on-device sensor (vision, audio, IMU, biomedical, etc.) data analytics at extremely low power, typically in the mW range and below, and hence enabling a variety of always-on use-cases and targeting battery operated devices.[^1]

This repository will implement most of the chapters from the book [TinyML Cookbook](https://www.amazon.com/TinyML-Cookbook-artificial-intelligence-ultra-low-power/dp/180181497X) by Gian Iodice &amp; Ronan Naughton. And will implement other interesting applications related to the Arduino Nano 33 BLE Sense Rev2!

## MicroController Boards

**Arduino Nano 33 BLE Sense Rev2**

| | Description |
| --- | --- |
| CPU | Arm Cortex-M4 64MHz |
| FLASH | 1MB |
| RAM | 256KB |
| SIZE | 45x18mm |

As bought and documented [here](https://store-usa.arduino.cc/products/nano-33-ble-sense-rev2?selectedStore=us)

**Rasperry Pi Pico W RP2040 MicroController**

| | Description |
| --- | --- |
| CPU | Dual core Arm Cortex-M0+ 133MHz |
| FLASH | 2MB |
| RAM | 264KB |
|Wifi| 2.4GHz single band, 802.11n 
| SIZE | 51x21mm |

As bought and documented [here](https://www.adafruit.com/product/5526)

## Book: Voice Controlling LEDS with Edge Impulse

**Gathering Data, Training, Optimizing, & Testing Model**

[![voice controlling leds](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Screenshot%20from%202023-03-04%2013-15-56.png)](https://studio.edgeimpulse.com/public/193428/latest/learning/keras/8)

## Book: Indoor Scene Classification

**Camera Setup**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0312.jpg)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0315.jpg)


**Scene Classification**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmp70nqe3ui.PNG)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmpcw8zqjn7.PNG)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmpehal6xl2.PNG)

## Project: Get Started With Machine Learning on Arduino

Implementation of [Get Started With Machine Learning on Arduino](https://docs.arduino.cc/tutorials/nano-33-ble-sense-rev2/get-started-with-machine-learning#capturing-gesture-training-data) by Sandeep Mistry and Dominic Pajak. A gesture classifier is created to play Street Fighter as detailed by Charlie Gerard in [Play Street Fighter with body movements using Arduino and Tensorflow.js](https://medium.com/@devdevcharlie/play-street-fighter-with-body-movements-using-arduino-and-tensorflow-js-6b0e4734e118). Full implementation can be found [here](https://github.com/arduino/AIoT-Dev-Summit-2019)

### Getting Gesture Data with BMI270 and BMM150 Sensors

The x-axis represents the num of samples and the y-axis represents g-force from the accelerometer and degrees per second from the gyroscope. 

**Jab Data**

Acceleration Graph:

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/jab_accel.jpg)

Angular velocity Graph:

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/jab_gyro.jpg)

Raw data can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/punch.csv)

**Upper Cut Data**

Acceleration Graph:

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/upper_accel.jpg)

Angular velocity Graph:

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/upper_gyro.jpg)

Raw data can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/upper_cut.csv)

### Training and Validation Learning Curves 

The learning curves after 300 epochs of training mixed with validation as seen below:

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Training_val_loss_.jpg)

with the following model and trainable paramaters:

| Layer (type)| Output Shape| Param #|
| ------------- | ------------- |--------|
| Dense | 50| 35,750|
| Dense | 15| 765|
| Dense | 2| 32|

### Gesture Sense Emmoji Keyboard

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/streetfighter.png)](https://youtu.be/awRqHDJUKUs)

Ino Code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/gestureDetection_classifier/gestureDetection_classifier.ino)

C-Byte Model can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/gestureDetection_classifier/model.h)

## Project: Reading Temperature&Humidity Values over Bluetooth

The blue box represents temperature and the red box represents humidity (room kinda hot lol)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/homescreen.png)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/SensorReads.png)

## Project: Person Detection 

### Arduino Nano 33 BLE Sense Rev2

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0328(1).jpg)](https://youtu.be/d5dRwel8NFQ)

Implementation of the person detection example as detailed by the Official Tenserflow Repo as of Oct 9, 2019 and [anaferrez's implemenation](https://projecthub.arduino.cc/anaferraz/ee255f8f-ba55-4e0a-93b2-3d4d373e7c8d). In my code, for the Nano 33 BLE Sense Rev2 board, when a person is detected (within the model's degrees of confidence) onboard led turns RED; when a person is not detected (again within the model's degrees of confidence) onboard led turns GREEN; and all other times flashes BLUE. As seen from the video, inferencing is not super accurate but pretty good! The Nano 33 BLE Sense Rev2 board is connected to the [ArduCam OV2640 MINI 2MP-Plus](https://www.amazon.com/dp/B012UXNDOY?ref_=pe_386300_442746000_DDT_E_DDE_dt_1)

Ino Code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/person_detection_OV2640Mini2MPlus.ino)

C-Byte Model can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/person_detect_model_data.cpp)

TFLM Image Processing code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/image_provider.cpp)

TFLM Person detection code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/detection_responder.cpp)

And all the other files such as required headers can be found in this [directory](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/person_detection_OV2640Mini2MPlus) that need to be included in the sketch for it to run.[^2]

## Rasperry Pi Pico W 

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0336(1).jpg)](https://www.youtube.com/watch?v=MaYkYJmJrqk)

Implementation of the person detection example as detailed by the [ArduCam Team](https://github.com/ArduCAM/RPI-Pico-Cam)

## LED Project: 24-LED NeoPixel

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/ledRing.png)](https://youtu.be/hxCp7cTqXQk)

## Project: Drone Flight Controller using the Arduino Nano 33 BLE Sense Rev2

WARNING!!! THIS PROJECT IS AN OPEN SOURCE HARDWARE PROJECT, SO WARNINIG!!! READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) BEFORE USING!!!!

This project stems from Montvydas in which he developed an Arduino Nano Quadcopted as found here: [Arduino Nano Quadcopter](https://www.instructables.com/Arduino-micro-Quadcopter/). I wanted to design my own flight controller system using the same prinicples from Montvydas Project. This project uses the Arduino Nano 33 BLE Sense Rev2 as the main contoller and will incorporate the Nano 33 BLE Sense Rev2 for its AI capabilites using the [Arducam Mini Module 5MP Plus OV5642](https://www.amazon.com/dp/B013JUKZ48/ref=sspa_dk_detail_0?psc=1&pd_rd_i=B013JUKZ48&pd_rd_w=ZOLHi&content-id=amzn1.sym.0d1092dc-81bb-493f-8769-d5c802257e94&pf_rd_p=0d1092dc-81bb-493f-8769-d5c802257e94&pf_rd_r=N4BZXPBP4T07WSD3WTVA&pd_rd_wg=ID8SA&pd_rd_r=286a49c2-6c11-459f-a6f0-a719a400a8db&s=industrial&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWwy) camera for scene classification and person detection purposes. Since the Arduino Nano 33 BLE Sense Rev2 already contains a built in IMU unit, Pressure sensor, and Bluetooth, alot of the modules found in  Montvydas Project have been removed. The only thing I added was a step-up voltage converter/booster for the lipo 3.7V+ battery that powers Nano 33 BLE Sense Rev2. The finished  schematic version and Pcb is shown below.

### Schematic and PCB layout:

Below is the PCB Schematic that will house the Arduino Nano 33 BLE Sense Rev 2 Flight Controller. Basically follows the [Arduino Nano Quadcopter](https://www.instructables.com/Arduino-micro-Quadcopter/) PCB Schematic only slight differences as mentioned above:

**Schematic**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/SCH_nano_carrier_th_0-nano_carrier_th_1_2023-06-04.png)

[EasyEda](https://easyeda.com/) includes a great free feature of seeing what the completed PCB will look like once produced and assembeld, as shown below:

**3D CAD Top View**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/3D_PCB5_2023-06-04.png)

**3D CAD Side View**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/3D_PCB5_2023-06-04(1).png)

**Gerber file and 3D Gerber CAD VIEW**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/3D_PCB5_2023-06-04(2).png)

[Gerber File](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/Gerber_PCB5_2023-06-04.zip)

**Bill of Materials Spreedsheet**

[BOM](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Drone/Hardware/BOM_Board1_PCB5_2023-06-04.ods)

### PCB Fabrication and Assembly:

PCB Fabrication and assembly was done by [EasyEda](https://easyeda.com/).

**Top View**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0366.jpg)

**Side View**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0368.jpg)

**Test Bed for Programming the Flight Control System**
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0371.jpg)

### Programming the Flight Control System: 

**Bluetooth® Low Energy Communication and Joystick Control**

WARNING!!! THIS CODE CONTAINS BLUETOOTH COMMUNICATION AND MAY INTERFERE WITH OTHER BLUETOOTH APPLICAATIONS!!! WARNINIG!!! READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) BEFORE USING!!!!

As Montvydas detailed, the Arduino Nano 33 BLE Sense (and Rev 2) contains [Bluetooth® Low Energy](https://docs.arduino.cc/tutorials/nano-33-ble-sense/ble-device-to-device) processing capabilities. To take advantage of this feature, I decided to use the communication protocol for the Drone's Joystick Control. As detailed in the [Bluetooth® Low Energy](https://docs.arduino.cc/tutorials/nano-33-ble-sense/ble-device-to-device) tutorial two Nano 33 BLE devices are used, one for the Host and one for the client. In this case, I decided for the Aruino Nano 33 BLE Sense to be the Host device in which a joystick(s) is hooked up to control the Drone's motorspeed as detailed by Ben Finio in his article [Drone Control with an Analog Joystick](https://www.sciencebuddies.org/stem-activities/drone-arduino-steering-joystick). The Client in this case is the Arduino Nano 33 BLE Sense Rev 2 that sends out the PWM pulses to the Drone's motors. The code for each device is located below:

HOST/SERVER/CENTRAL DEVICE:

[Central Device](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/Drone/Software/central_joystick)

CLIENT/PERIPHERAL DEVICE:

[Peripheral Device](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/Drone/Software/perp_motor_control)

**Velocity,Gyroscope and Altitude Control**

**PID Controller**



### Testing and Resuslts:

-------------------------------------------------------------------------------
## Reference:
[^1]: [TinyML](https://www.tinyml.org/about/)
[^2]: Need to also get the get [ArduCam OV2640 MINI 2MP-Plus header file](https://github.com/ArduCAM/Arduino); choose the right camera module in the memorysaver.h; and download the JPEG library for things to work
