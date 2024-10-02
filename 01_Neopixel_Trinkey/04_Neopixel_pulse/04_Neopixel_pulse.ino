#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill(0xFF00AA);    // set pixel color (HEX red)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  pixels.fill(0xFF00AA);    // set color
  int b = map(sin(millis()/1000.0)*1000, -1000, 1000, 0, 255);  // mapping sinus pulse -> change /1000.0 for speed
  pixels.setBrightness( b ); // set a number from 10 to 255 for brightness
  pixels.show();            // without show there will be no update
}
