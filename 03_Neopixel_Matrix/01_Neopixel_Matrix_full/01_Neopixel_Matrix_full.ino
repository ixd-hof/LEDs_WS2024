#include <seesaw_neopixel.h>

#define NUMPIXELS 8 * 8   // number of neopixels
#define PIN_NEODRIVER 15  // Neodriver pin

//seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);  // blue

void setup() {
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
}

void loop() {
  pixels.clear();  // clear LED ring

  for (int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, 255, 0, 100);
    pixels.show();           // uncomment for incrementing light-up (otherwise all at once)
    delay(200);              // speed / delay of incremental light-up
  }

  pixels.show();                // without show there will be no update
  delay(200);                   // set speed / slowdown
}