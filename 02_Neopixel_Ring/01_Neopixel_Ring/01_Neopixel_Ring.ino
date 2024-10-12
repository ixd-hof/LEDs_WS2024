#include <seesaw_neopixel.h>

#define NUMPIXELS        24  // number of neopixels
#define PIN_NEODRIVER     15  // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);

void setup() {
  pixels.begin(0x60);           // initialize neopixels with neodriver address
  pixels.setBrightness(20);     // set lower brightness
  pixels.show();
}

void loop() {
  pixels.clear();			          // clear LED ring

  pixels.setPixelColor(0, 255, 0, 100);   // set color of first (0) pixel to red
  pixels.setPixelColor(1, 255, 0, 100);
  pixels.setPixelColor(2, 255, 0, 100);
  pixels.setPixelColor(3, 255, 0, 100);
  pixels.setPixelColor(4, 255, 0, 100);
  pixels.setPixelColor(5, 255, 0, 100);
  pixels.setPixelColor(6, 255, 0, 100);
  pixels.setPixelColor(7, 255, 0, 100);
  pixels.setPixelColor(8, 255, 0, 100);
  pixels.setPixelColor(9, 255, 0, 100);
  pixels.setPixelColor(10, 255, 0, 100);
  pixels.setPixelColor(11, 255, 0, 100);
  pixels.setPixelColor(12, 255, 0, 100);
  pixels.setPixelColor(13, 255, 0, 100);
  pixels.setPixelColor(14, 255, 0, 100);
  pixels.setPixelColor(15, 255, 0, 100);
  pixels.setPixelColor(16, 255, 0, 100);
  pixels.setPixelColor(17, 255, 0, 100);
  pixels.setPixelColor(18, 255, 0, 100);
  pixels.setPixelColor(19, 255, 0, 100);
  pixels.setPixelColor(20, 255, 0, 100);
  pixels.setPixelColor(21, 255, 0, 100);
  pixels.setPixelColor(22, 255, 0, 100);
  // delay(200);
  pixels.setPixelColor(23, 255, 0, 100);

  pixels.show();                // without show there will be no update
  delay(200);                   // set speed / slowdown
}


/* or with less code

for (int i=0; i<NUMPIXELS; i++ {
  pixels.setPixelColor(i, 255, 0, 100);
}