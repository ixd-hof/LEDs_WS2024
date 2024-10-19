#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();  // initialize MPR121

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

void setup() {
  Serial.begin(9600);                      // enable serial console
  cap.begin(0x5A);                         // start touch sensor

  pixels.begin();                          // initialize neopixel(s)
  pixels.setBrightness(20);                // set brightness (0 low, 255 high)
  pixels.show();
}

void loop() {
  uint16_t touched = cap.touched();       // get touch id
  Serial.println(touched);                // print current id to console

  // touch pads (1-12): 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048

  if (touched == 32) // pad 5
    pixels.setPixelColor(0, 0, 100, 255);
  else if (touched == 64) // pad 6
    pixels.setPixelColor(0, 255, 0, 100);
  else
    pixels.setPixelColor(0, 0, 0, 0);   // otherwise black
  
  pixels.show();
}