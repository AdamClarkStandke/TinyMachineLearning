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


## Project: Person Detection 

### Arduino Nano 33 BLE Sense Rev2

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0328(1).jpg)

Implementation of the person detection example as detailed by the Official Tenserflow Repo as of Oct 9, 2019 and [anaferrez's implemenation](https://projecthub.arduino.cc/anaferraz/ee255f8f-ba55-4e0a-93b2-3d4d373e7c8d). In my code, for the Nano 33 BLE Sense Rev2 board, when a person is detected (within the model's degrees of confidence) onboard led turns RED; when a person is not detected (again within the model's degrees of confidence) onboard led turns GREEN; and all other times flashes BLUE. As seen from the video, inferencing is not super accurate but pretty good! The Nano 33 BLE Sense Rev2 board is connected to the [ArduCam OV2640 MINI 2MP-Plus](https://www.amazon.com/dp/B012UXNDOY?ref_=pe_386300_442746000_DDT_E_DDE_dt_1)

Ino Code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/person_detection_OV2640Mini2MPlus.ino)

C-Byte Model can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/person_detect_model_data.cpp)

TFLM Image Processing code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/image_provider.cpp)

TFLM Person detection code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/person_detection_OV2640Mini2MPlus/detection_responder.cpp)

And all the other files such as required headers can be found in this [directory](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/person_detection_OV2640Mini2MPlus) that need to be included in the sketch for it to run.[^2]

### Rasperry Pi Pico W 

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0336(1).jpg)](https://www.youtube.com/watch?v=MaYkYJmJrqk)

Implementation of the person detection example as detailed by the [ArduCam Team](https://github.com/ArduCAM/RPI-Pico-Cam)


## Project: Drone Flight Controller using the Arduino Nano 33 BLE Sense Rev2

WARNING!!! THIS PROJECT IS AN OPEN SOURCE HARDWARE PROJECT TAKE ALL PRECATIONS BEFORE ASSEMBLY SUCH AS MASK, GLOVES AND FIRE EXTINGUISHER. IN THAT REGARD READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) ALSO  BEFORE USING!!!!

This project stems from Montvydas in which he developed an Arduino Nano Quadcopted as found here: [Arduino Nano Quadcopter](https://www.instructables.com/Arduino-micro-Quadcopter/). I wanted to design my own flight controller system using the same prinicples from Montvydas Project. This project uses the Arduino Nano 33 BLE Sense Rev2 as the main contoller and will incorporate the Nano 33 BLE Sense Rev2 for its AI capabilites, namely I will be using the [TLFM](https://github.com/tensorflow/tflite-micro) library to train a [PPO agent](https://docs.ray.io/en/master/rllib/rllib-algorithms.html#ppo) to control the drone's flight system (i.e. its motors). 

### (Old Version) Schematic and PCB layout:

This was the first version of the PCB flight control system. Eventhough it works, there were certain design elements that needed to be modified, such as the jst connectors for the battery and how the nano was powered. Thus, this version should not be used for assembly but is here for documentation purposes only!! 
  
Similar to Version two, since the Arduino Nano 33 BLE Sense Rev2 already contains a built in IMU unit, Pressure sensor, and Bluetooth, alot of the modules found in  Montvydas Project have been removed. The only thing I added was a step-up voltage converter/booster for the lipo 3.7V+ battery that powers Nano 33 BLE Sense Rev2. The finished  schematic version and Pcb is shown below

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

**PCB Fabrication and Assembly**

PCB Fabrication and assembly was done by [EasyEda](https://easyeda.com/). I created a test bed to program the drone as shown below:

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/test_bed_droneNano.png)](https://youtu.be/hVllpykUUsg)

Unlike the photo, the video uses [31mm Propellers](https://www.amazon.com/Propellers-Replacement-Eachine-Inductrix-Quadcopter/dp/B079DP3V42) that would fit [716 Brushed Motors](https://www.aliexpress.us/item/3256801308414101.html?gatewayAdapt=glo2usa4itemAdapt). The drone frame is from [Usmile®](https://www.amazon.com/usmile-Lightweight-Brushed-Quadcopter-Support/dp/B01MU440T0/ref=pd_bxgy_sccl_1/139-7860370-8970268?pd_rd_w=Vfa2j&content-id=amzn1.sym.26a5c67f-1a30-486b-bb90-b523ad38d5a0&pf_rd_p=26a5c67f-1a30-486b-bb90-b523ad38d5a0&pf_rd_r=VZWFDSZH27C90D7TXY30&pd_rd_wg=cUSfv&pd_rd_r=fc1c370a-43be-4ac0-86d6-d8efbbb1129c&pd_rd_i=B01MU440T0&psc=1) and the batteries are from [Sea Jump](https://www.amazon.com/sea-jump-Lithium-Quadcopter-Aircraft/dp/B07SLLVQ2Q/ref=sr_1_2?keywords=sea+jump&qid=1688439753&sr=8-2).

### (New Version) Schematic and PCB layout:

This is the updated version of the schematic--that is still a work in progress. Unlike the old version, the new version does not have a step-up voltage converter/booster. Also the camera layout has been changed to integrate (fingers crossed) a [Wolfwhoop WT06 Micro AIO 600TVL Camera](https://www.amazon.com/Wolfwhoop-600TVL-Camera-Transmitter-Antenna/dp/B06VY7L1N4/ref=asc_df_B06VY7L1N4/?tag=hyprod-20&linkCode=df0&hvadid=647222099437&hvpos=&hvnetw=g&hvrand=7687682336458292318&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9006620&hvtargid=pla-1458319804946&gclid=CjwKCAjw44mlBhAQEiwAqP3eVuA56xiEOqQz-usnhdkRRYzCiu8g2hDIv2rGP2h5YuFzFXEjMHMy5RoCzkwQAvD_BwE&th=1) for video transmission. And for the PCB, I increased the trace width to 50 mil for the two battery sources and a seperate copper pour for the current powering the motor's.   

**Schematic**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/SCH_nano_carrier_th_0-nano_carrier_th_1_2023-07-03.png)

**3D CAD Top View**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/3D_PCB8_2023-07-03.png)

**Gerber file and 3D Gerber CAD VIEW**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/3D_PCB8_2023-07-03%20(1).png)

[Gerber File](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Gerber_PCB8_2023-07-03.zip)

**Bill of Materials Spreedsheet**

Same as old version, just without step-up voltage converter/booster module.

**PCB Fabrication and Assembly**

PCB Fabrication and assembly was done by [EasyEda](https://easyeda.com/).I created a test bed to program the drone as shown below:

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/top_view_testBed.jpg)](https://www.youtube.com/shorts/aawXR8qJVKw)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/side_view_testBed.jpg)

### Modeling:

For the drone frame, I decided to use the 95mm weelbase frame from [USAQ](https://www.amazon.com/QX95-Brushed-Racing-Quadcopter-Frame/dp/B08LTNT16B/ref=asc_df_B08LTNT16B/?tag=hyprod-20&linkCode=df0&hvadid=647363962209&hvpos=&hvnetw=g&hvrand=5681260871874349734&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9006620&hvtargid=pla-2161115067792&psc=1&gclid=CjwKCAjwzJmlBhBBEiwAEJyLuypXNVeizTEYKut4k5DIcBmoW73K6ttTfiu4gYklHUo_MqTt6zmK3RoCLiYQAvD_BwE)

Because the drone frames available in [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/gym_pybullet_drones/assets) are different from the drone frame that I will be using I needed to model the drone frame (as best I could) in [blender](https://www.blender.org/). That way it could be simulated kind of accurately in the [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/) rl environmnet. I used the [cf2.dae](https://github.com/utiasDSL/gym-pybullet-drones/blob/master/gym_pybullet_drones/assets/cf2.dae) as a template in regards to modeling the propellers:   

[Custom Drone](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/customDrone.dae)

I then created a [urdf file](http://wiki.ros.org/urdf) to import the collada file I created in blender and used the defualt properties, joints, and links found in the other drone frames in learning to fly.  

[RoboCain](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/droneOne.urdf)

And the drone frame was able to be simulated in the [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/) rl environment as seen below:

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/drone_frame.png)](https://youtu.be/o9qXMjsNjKY)

### Programming: 
READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) BEFORE GOING FURTHER!!!!

**Basic/Generic: Motor Contoller**

This is the code that needs to be uploaded to Arduino Nano 33 BLE Sense (and Rev 2) after constructing the Test Bed System to get the motors rotating: [Spinny Motors](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/motor_control/motor_control.ino)

**Basic/Generic: Bluetooth® Low Energy Joystick Controller**

WARNING!!! THIS CODE CONTAINS BLUETOOTH COMMUNICATION AND MAY INTERFERE WITH OTHER BLUETOOTH APPLICAATIONS!!! WARNINIG!!! READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) BEFORE USING!!!!

As Montvydas detailed, the Arduino Nano 33 BLE Sense (and Rev 2) contains [Bluetooth® Low Energy](https://docs.arduino.cc/tutorials/nano-33-ble-sense/ble-device-to-device) processing capabilities. To take advantage of this feature, I decided to use the communication protocol for the Drone's Joystick Control. As detailed in the [Bluetooth® Low Energy](https://docs.arduino.cc/tutorials/nano-33-ble-sense/ble-device-to-device) tutorial two Nano 33 BLE devices are used, one for the Host and one for the client. In this case, I decided for the Aruino Nano 33 BLE Sense to be the Host device in which a joystick(s) is hooked up to control the Drone's motorspeed as detailed by Ben Finio in his article [Drone Control with an Analog Joystick](https://www.sciencebuddies.org/stem-activities/drone-arduino-steering-joystick). The Client in this case is the Arduino Nano 33 BLE Sense Rev 2 that sends out the PWM pulses to the Drone's motors. The code for each device is located below:

HOST/SERVER/CENTRAL DEVICE:

[Central Device](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/Drone/Software/central_joystick)

CLIENT/PERIPHERAL DEVICE:

[Peripheral Device](https://github.com/AdamClarkStandke/TinyMachineLearning/tree/main/Drone/Software/perp_motor_control)

**Advanced: Neural Network Flight Controller**

To take advantage of the machine learning capabilities of the Arduino Nano 33 BLE Sense Rev 2, I decided to use the reinforcement learning enviornment [Learning to Fly](https://arxiv.org/abs/2103.02142) to train a PPO reinforcement learning agent for controlling the drone's motors.

### Testing and Resuslts:

-------------------------------------------------------------------------------
## Reference:
[^1]: [TinyML](https://www.tinyml.org/about/)
[^2]: Need to also get the get [ArduCam OV2640 MINI 2MP-Plus header file](https://github.com/ArduCAM/Arduino); choose the right camera module in the memorysaver.h; and download the JPEG library for things to work
