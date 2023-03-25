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

Implementation of [Get Started With Machine Learning on Arduino](https://docs.arduino.cc/tutorials/nano-33-ble-sense-rev2/get-started-with-machine-learning#capturing-gesture-training-data) by Sandeep Mistry and Dominic Pajak. A gesture classifier is created to play Street Fighter as detailed by Charlie Gerard in [Play Street Fighter with body movements using Arduino and Tensorflow.js](https://medium.com/@devdevcharlie/play-street-fighter-with-body-movements-using-arduino-and-tensorflow-js-6b0e4734e118).

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

## Reading Temperature&Humidity Values over Bluetooth

The blue box represents temperature and the red box represents humidity (room kinda hot lol)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/homescreen.png)

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/SensorReads.png)

-------------------------------------------------------------------------------
## Reference:
[^1]: [TinyML](https://www.tinyml.org/about/)
