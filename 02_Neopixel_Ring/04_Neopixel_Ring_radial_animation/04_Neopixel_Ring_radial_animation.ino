#include <seesaw_neopixel.h>

#define NUMPIXELS 24      // number of neopixels
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

  for (int i=0; i<NUMPIXELS; i++ {
    if (i == current_pixel)
        pixels.setPixelColor(i, 255, 0, 100);  // set only current pixel's color
    }
  }

  if (current_pixel < NUMPIXELS) // if smaller than 24 -> increase by one
    current_pixel += 1;
  else
    current_pixel = 0;

  pixels.show();            // without show there will be no update

  delay(200);               // set speed / slowdown

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