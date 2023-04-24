//NeoPixel Ring Code (c) Arnov Sharma
//Arnov Sharma
//Orginally Published May 5, 2019 © LGPL

//Modification: Adam Standke April, 23, 2023  © LGPL 

#include <Adafruit_NeoPixel.h>


#define BUTTON_PIN   7 

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24

// Initialization of showType variable
int showType = 0; 

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Initialization of oldState variable
bool oldState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Reading Button input
  pixels.begin(); // INITIALIZE NeoPixel Ring object (REQUIRED)
  pixels.show(); 
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > 6)
        showType=0;
      startShow(showType);
    }
  }
  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(pixels.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(pixels.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(pixels.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(pixels.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(pixels.Color(127,   0,   0), 50); // Red
            break;
    case 5: theaterChase(pixels.Color(  0,   0, 127), 50); // Blue
            break;
    case 6: theaterChaseRainbow(50);
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<24; i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < 24; i=i+3) {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);
      for (int i=0; i < 24; i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < 24; i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < 24; i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
