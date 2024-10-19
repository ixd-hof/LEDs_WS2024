#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <hp_BH1750.h>  //  include the library
hp_BH1750 BH1750;       //  create the light sensor

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);                      // enable serial console
  BH1750.begin(BH1750_TO_GROUND);          // initialize light sensor

  pixels.begin();                          // initialize neopixel(s)
  pixels.setBrightness(20);                // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(255, 0, 100) );// set pixel color (RGB magenta)
}

void loop() {
  // put your main code here, to run repeatedly:
  BH1750.start();               // start measurement
  float lux = BH1750.getLux();  // wait until a conversion finished (0-4096)
  Serial.println(lux);          // print value to console
  
  int b = map (lux, 0, 4096, 1, 100);
  pixels.setBrightness(b);      // set brightness relative to sensor value
  pixels.show();
}
