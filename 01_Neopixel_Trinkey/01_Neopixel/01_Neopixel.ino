#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)
#define PIN_NEOPIXEL     6  // for emulator or Pico

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(255, 0, 100) );    // set pixel color (RGB magenta)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  // noting yet
}
