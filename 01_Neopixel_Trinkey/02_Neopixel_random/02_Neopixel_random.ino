#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)
#define PIN_NEOPIXEL     6  // for emulator or Pico

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(255, 0, 0) );    // set pixel color (RGB red)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  pixels.fill( pixels.Color(255, 0, 0) );    // set color
  pixels.setBrightness( random(10, 255) ); // set a number from 10 to 255 for brightness
  pixels.show();            // without show there will be no update
  delay(200);               // interval speed
}
