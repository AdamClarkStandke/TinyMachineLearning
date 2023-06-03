/* Drone Steering Code
 *  
 *  Ben Finio, Science Buddies
 *  2021
 *  
 *  For written instructions and circuit diagram please visit
 *  https://www.sciencebuddies.org/stem-activities/drone-arduino-steering-joystick
 *  
 *  physical layout of drone motors
 *  
 *  (1)    (4)
 *     \  /
 *      \/
 *      /\
 *     /  \
 *  (2)    (3)
 *  
 */
 
// declare global variables

// constants that won't change
const int motor1pin = 11;       // pin for motor 1
const int defaultSpeed = 130;   // default PWM value
const int speedChange = 90;     // PWM value to add or subtract
const int ramp_delay = 40;      // loop delay time for motor ramp up in milliseconds
const float a = 0.3;            // constant for converting analog voltages to PWM values
const float b = 1.5;            // offset for converting voltages to PWM values

// variables that can change
int motor1speed = defaultSpeed;      // motor 1 PWM value between 0-255
float UD = 0;                        // analog voltage from joystick up/down motion
float LR = 0;                        // analog voltage from joystick left/right motion

void setup() { // code that only runs once
  // 
  Serial.begin(9600); // initialize serial communication, use for debugging if needed. Select Tools --> Serial Monitor to open window. 
  int speed = 0; // ramp up slowly to default speed
  while(speed<defaultSpeed){
     // write PWM values to motor pins
     analogWrite(motor1pin,speed);
     analogWrite(motor2pin,speed);
     analogWrite(motor3pin,speed);
     analogWrite(motor4pin,speed); 
     speed++;            // increment speed
     delay(ramp_delay);  // short delay
  }
}

void loop() {  // code that loops repeatedly

  //change to read communication
  LR = analogRead(A0);     // read analog joystick voltage from pin A0, returns an integer from 0-1023
  UD = analogRead(A1);     // read analog joystick voltage from pin A1, returns an integer from 0-1023
  LR = 5*LR/1023;          // convert to a voltage from 0-5V
  UD = 5*UD/1023;          // convert to a voltage from 0-5V

  // convert analog voltages to motor speeds
  motor1speed = defaultSpeed+speedChange*(a*UD-a*LR);
  motor2speed = defaultSpeed+speedChange*(a*UD+a*LR-b);
  motor3speed = defaultSpeed+speedChange*(-a*UD+a*LR);
  motor4speed = defaultSpeed+speedChange*(-a*UD-a*LR+b);
  

  // send PWM signals to all 4 motors
  analogWrite(motor1pin,motor1speed);
  

  // Print information for debugging purposes
  // Comment out this code if you don't need it
  Serial.print("UD: ");
  Serial.print(UD);
  Serial.print("  LR: ");
  Serial.print(LR);
  Serial.print("  Motor 1: ");
  Serial.print(motor1speed);
  Serial.println();

}
