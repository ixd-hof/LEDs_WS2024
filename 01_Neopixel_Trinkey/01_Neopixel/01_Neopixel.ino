#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill(0xFF00AA);    // set pixel color (HEX magenta)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  // noting yet
}
