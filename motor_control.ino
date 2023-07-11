const int motor1pin = 6;       // pin for motor 1
const int motor2pin = 5;       // pin for motor 2
const int motor3pin = 4;        // pin for motor 3
const int motor4pin = 3;        // pin for motor 4
const int defaultSpeed = 255;   // default PWM value
const int speedChange = 100;     // PWM value to add or subtract
const int ramp_delay = 100;      // loop delay time for motor ramp up in milliseconds

int motor1speed = defaultSpeed;      // motor 1 PWM value between 0-255
int motor2speed = defaultSpeed;      // motor 2 PWM value between 0-255
int motor3speed = defaultSpeed;      // motor 3 PWM value between 0-255
int motor4speed = defaultSpeed;      // motor 4 PWM value between 0-255

void setup () {
    
  Serial.println(" ");
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
while(speed>0){
     // write PWM values to motor pins
    analogWrite(motor1pin,speed);
    analogWrite(motor2pin,speed);
    analogWrite(motor3pin,speed);
    analogWrite(motor4pin,speed); 
    speed--;            // increment speed
    delay(ramp_delay);  // short delay
  
}

}
void loop () {}