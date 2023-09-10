# TinyMachineLearning

Developing Embedded Applications that for the most part deal with machine learning as detailed from the following books and tutorials:

*[TinyML Cookbook by Gian Iodice](https://www.packtpub.com/product/tinyml-cookbook/9781801814973)
*[Teach an Arduino to Fly by David McGriffy](https://www.makershed.com/products/make-drones-pdf)

As Gian details Tiny machine learning is broadly defined as a fast growing field of machine learning technologies and applications including hardware (dedicated integrated circuits), algorithms and software capable of performing on-device sensor (vision, audio, IMU, biomedical, etc.) data analytics at extremely low power, typically in the mW range and below, and hence enabling a variety of always-on use-cases and targeting battery operated devices.[^1]

This Branch contains the most updated code and hardware designs. The branch old_documentation contains older code/designs and applications that do not fit with the main repo. 

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

## Project: Gesture Sense Emmoji Keyboard

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

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/streetfighter.png)](https://youtu.be/awRqHDJUKUs)

Ino Code can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/gestureDetection_classifier/gestureDetection_classifier.ino)

C-Byte Model can be found [here](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/gestureDetection_classifier/model.h)

## Project: Person Detection with Rasperry Pi Pico W

Implementation of the person detection example as detailed by the [ArduCam Team](https://github.com/ArduCAM/RPI-Pico-Cam)

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0336(1).jpg)](https://www.youtube.com/watch?v=MaYkYJmJrqk)

## Project: Drone Flight Control System using the Arduino Nano 33 BLE Sense Rev2 Board 

WARNING!!! THIS PROJECT IS AN OPEN SOURCE HARDWARE PROJECT TAKE ALL PRECATIONS BEFORE ASSEMBLY SUCH AS MASK, GLOVES AND FIRE EXTINGUISHER. IN THAT REGARD READ THE [MIT LICENSE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/LICENSE) ALSO  BEFORE USING!!!!

### Schematic and PCB layout:

This version of the schematic comes from the book [Teach an Arduino to Fly by David McGriffy](https://www.makershed.com/products/make-drones-pdf) in the book David uses the [Teensy 3.1](https://www.pjrc.com/teensy/teensy31.html) board and the add-in for the Arduino IDE to program the flight controller, I just switched the board and removed the  components that are not necessary for the Nano BLE 33 Rev 2. This design uses only one 3.7V 650mAh battery rather then the two that I used in the previous two designs. This should help with the weight issues I was having. To make this design work you need to buy a voltage regulator/booster (similar to the one I designed in Old Version 1) except in this design I bought a tried and tested booster (rather than design my own like I did in Old Version 1); in particular I bought [Matek VB2A5V 3-4.2V to 5V Voltage Booster ](https://www.racedayquads.com/products/matek-vb2a5-1s-lipo-to-5v-voltage-booster?currency=USD&variant=31467728207985&gclid=Cj0KCQjw0IGnBhDUARIsAMwFDLnRW7vPnVI_kPZZ07VLbTDB3pQNJlU3sNtUL8EGRetb_AuOmo7wnHUaAl3fEALw_wcB). Basically, the genius of David's design is that a 3.7v battery can be used to power the Arduino, motors, and other components. The battery's 3.7-4.2 variable discharge rate will power the motors, while the regulated 5v output  will power the Arduino through its vin pin and the auxiliary components (i.e a camera). The Arduino's 3v3 pin will power the [Lemon RX reciever](https://lemon-rx.com/index.php?route=product/product&product_id=263) to be controlled by the [Blade MLP4DSM 4Ch Controller](https://www.horizonhobby.com/product/mlp4dsm-4ch-transmitter-2.4ghz-bmcx2120sr/EFLH1064B.html?gclid=Cj0KCQjw0IGnBhDUARIsAMwFDLnIMOxdLQWNxmZvSB9TNVZfrrQnBrdQ40ycnGwFcJZ92rF96O86bkgaAlpqEALw_wcB) I will be using the drone frame from  David's book and modify David's code as found at [The visible drone](http://www.makedronesbook.com/projects/VizDrone). Get David's book to fully understand this Drone/flight control game, G!!! (highly recommend). 

**Schematic**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/arduinoDrone_schem.png)

**Gerber file and 3D Gerber CAD VIEW**

![](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/3D_PCB_PCB_ArudinoDrone_2023-08-19_2023-08-19.png)

[Gerber File](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/Gerber_PCB_PCB_ArudinoDrone_2023-08-19_2023-08-20.zip)


**PCB Fabrication and Assembly**

PCB Fabrication and assembly was done by [EasyEda](https://easyeda.com/).I created a test bed to program the drone as shown in the photos below. The drone frame is a [Syma X5C Frame](https://www.amazon.com/Syma-Channel-2-4GHz-Explorers-Copter/dp/B00MNG37C2/ref=asc_df_B00MNG37C2/?tag=hyprod-20&linkCode=df0&hvadid=312184153387&hvpos=&hvnetw=g&hvrand=2952487919274782735&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9006587&hvtargid=pla-587640326317&psc=1) 

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/IMG_0478.jpg)](https://youtu.be/VT2iOiBPnwo)


### Modeling:

Because the drone frames available in [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/gym_pybullet_drones/assets) are different from the drone frame that I will be using I needed to model the drone frame (as best I could) in [blender](https://www.blender.org/). That way it could be simulated kind of accurately in the [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/) rl environmnet. I used the [cf2.dae](https://github.com/utiasDSL/gym-pybullet-drones/blob/master/gym_pybullet_drones/assets/cf2.dae) as a template in regards to modeling the propellers:   

[Custom Drone](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/customDrone.dae)

I then created a [urdf file](http://wiki.ros.org/urdf) to import the collada file I created in blender and used the defualt properties, joints, and links found in the other drone frames in learning to fly.  

[RoboCain](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/droneOne.urdf)

And the drone frame was able to be simulated in the [learning to fly](https://github.com/utiasDSL/gym-pybullet-drones/tree/master/) rl environment as seen below in the fly.py example:

[![CLICK HERE](https://github.com/AdamClarkStandke/TinyMachineLearning/blob/main/drone_frame.png)](https://youtu.be/o9qXMjsNjKY)

### Coding, Testing and Resuslts:

-------------------------------------------------------------------------------
## Reference:
[^1]: [TinyML](https://www.tinyml.org/about/)
[^2]: Need to also get the get [ArduCam OV2640 MINI 2MP-Plus header file](https://github.com/ArduCAM/Arduino); choose the right camera module in the memorysaver.h; and download the JPEG library for things to work
