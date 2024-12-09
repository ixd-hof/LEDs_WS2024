#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "Adafruit_LTR390.h"  //  include the library
Adafruit_LTR390 ltr = Adafruit_LTR390(); //  create the light sensor

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);                      // enable serial console
  ltr.begin();                             // initialize light sensor
  ltr.setMode(LTR390_MODE_UVS);            // set UV mode
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  pixels.begin();                          // initialize neopixel(s)
  pixels.setBrightness(20);                // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(255, 0, 100) );// set pixel color (RGB magenta)
}

void loop() {

  if (ltr.newDataAvailable()) {
    Serial.print("UV data: "); 
    Serial.print(ltr.readUVS());

    int b = map (ltr.readUVS(), 0, 200, 1, 100);
    pixels.setBrightness(b);      // set brightness relative to sensor value
    pixels.show();
  }
}