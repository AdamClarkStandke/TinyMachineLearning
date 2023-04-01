# TinyMachineLearning

Developing Embedded Applications from the book TinyML Cookbook by Gian Iodice &amp; Ronan Naughton. 

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

**Rasperry PI**

| | Description |
| --- | --- |
| CPU | Dual core Arm Cortex-M0+ 133MHz |
| FLASH | 2MB |
| RAM | 264KB |
| SIZE | 51x21mm |

## Chapter 4: Voice Controlling LEDS with Edge Impulse

**Gathering Data, Training, Optimizing, & Testing Model**

[![voice controlling leds](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Screenshot%20from%202023-03-04%2013-15-56.png)](https://studio.edgeimpulse.com/public/193428/latest/learning/keras/8)

## Chapter 5: Indoor Scene Classification

**Camera Setup**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0312.jpg)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0315.jpg)


**Scene Classification**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmp70nqe3ui.PNG)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmpcw8zqjn7.PNG)
![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/tmpehal6xl2.PNG)

## Get Started With Machine Learning on Arduino

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

C-Bytye Model can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/gestureDetection_classifier/model.h)

## Reading Temperature&Humidity Values over Bluetooth

The blue box represents temperature and the red box represents humidity (room kinda hot lol)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/homescreen.png)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/SensorReads.png)

## Person Detection 

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0328.jpg)](https://youtu.be/vxXALj3QExY)

Implementation of the person detection example as detailed by the Official Tenserflow Repo as of Oct 9, 2019 and [anaferrez's implemenation](https://projecthub.arduino.cc/anaferraz/ee255f8f-ba55-4e0a-93b2-3d4d373e7c8d). In this case, for the Nano 33 BLE Sense Rev2 board, when a person is detected (within the model's degrees of confidence) onboard led turns RED; when a person is not detected (again within the model's degrees of confidence) onboard led turns GREEN; and all other times flashes BLUE. As seen from the video, inferencing is not super accurate but pretty good! The Nano 33 BLE Sense Rev2 board is connected to the [ArduCam OV2640 MINI 2MP-Plus](https://www.amazon.com/dp/B012UXNDOY?ref_=pe_386300_442746000_DDT_E_DDE_dt_1)

Ino Code can be found [here]

C-Bytye Model can be found [here]

TFLM Image Processing code can be found [here]

TFLM Person detection code can be found [here]

And all the other files such as required headers can be found in this [directory]



-------------------------------------------------------------------------------
## Reference:
[^1]: [TinyML](https://www.tinyml.org/about/)
