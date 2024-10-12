#include <seesaw_neopixel.h>

#define NUMPIXELS 24      // number of neopixels
#define PIN_NEODRIVER 15  // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);

void setup() {
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
}

int b = 0;

void loop() {
  pixels.clear();

  pixels.setBrightness(b);  // set current value of b to brightness
  for (int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, 255, 0, 100); // set color
  }

  pixels.show();            // without show there will be no update

  if (b < 100) {            // if brightness b is lower than 100 %
    b += 1;                 // increase brightness by one
  }
  else {                    // if 255 then set to 0 and start again
    b = 0;
    //delay(1000);          // wait a second after full brightness
  }
  //delay(200);               // set speed / slowdown increase

}