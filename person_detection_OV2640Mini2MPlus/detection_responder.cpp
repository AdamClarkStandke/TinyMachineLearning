/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "detection_responder.h"

#include "Arduino.h"

// Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
const int led_red = 22;
const int led_green = 23;
const int led_blue = 24;

// Flash the blue LED after each inference
void RespondToDetection(tflite::ErrorReporter* error_reporter,
                        uint8_t person_score, uint8_t no_person_score) {
  static bool is_initialized = false;
  if (!is_initialized) {
    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_blue, OUTPUT);
    is_initialized = true;
  }

  // Switch the person/not person LEDs off due to individual LEDs be active LOW
  digitalWrite(led_green, HIGH);
  digitalWrite(led_red, HIGH);

  // Flash the blue LED after every inference.
  digitalWrite(led_blue, LOW);
  delay(100);
  digitalWrite(led_blue, HIGH);

  // Switch the red LED on when a person is detected,
  // and switch the green led on when no person is detected
  if (person_score > no_person_score) {
    digitalWrite(led_green, HIGH);
    //should only give RED light on now 
    digitalWrite(led_red, LOW);
  } else {
    //should only give GREEN light on now
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
  }

  error_reporter->Report("Person score: %d No person score: %d", person_score,
                         no_person_score);
}
