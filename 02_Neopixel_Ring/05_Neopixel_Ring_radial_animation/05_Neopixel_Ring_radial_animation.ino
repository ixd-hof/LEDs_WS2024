#include <seesaw_neopixel.h>

#define NUMPIXELS 12      // number of neopixels
#define PIN_NEODRIVER 15  // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);

void setup() {
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
}

int current_pixel = 0;

void loop() {
  pixels.clear();

  float s = sin(millis() / 1000.0) * 1000.0;
  float current_pixel = map(s, -1000, 1000, 0, NUMPIXELS);

  for (int i=0; i<NUMPIXELS; i++) {
    if (i == current_pixel) {
        pixels.setPixelColor(i, 255, 0, 100);  // set only current pixel's color
    }
    else {
      pixels.setPixelColor(i, 0, 0, 0);       // set other pixels to black
    }
  }

  pixels.show();            // without show there will be no update

  //delay(200);               // set speed / slowdown

}

/* // smooth variant

  for (int i=0; i<NUMPIXELS; i++ {
    if (i == current_pixel)
      for (int b=0; b<100; b++) {
        pixels.setBrightness(b); // increase brightness (of all pixels but showing only one)
        pixels.setPixelColor(i, 255, 0, 100);  // set only current pixel's color
        pixels.show(); // show pixels (in loop fo immediate effect)
      }
    }
  }
*/