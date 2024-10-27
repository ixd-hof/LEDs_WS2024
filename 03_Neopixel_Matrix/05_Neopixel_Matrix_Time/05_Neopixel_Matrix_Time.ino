#include <seesaw_neopixel.h>

#define NUMPIXELS 64 // 24      // number of neopixels
#define PIN_NEODRIVER 15        // Neodriver pin

//seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin();

  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
}

int current_pixel = 0;

void loop() {
  pixels.clear();

  // minutes since start
  current_pixel = millis()/1000/60;
  //Serial.println(current_pixel);

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0);  // set other pixels to black
  }

  for (int i = 0; i < current_pixel; i++) {
    pixels.setPixelColor(i, 255, 0, 100);  // set current pixel to magenta
  }

  // blink seconds
  pixels.setPixelColor(current_pixel, 255, 0, 100);
  pixels.show();
  delay(1000);
  pixels.setPixelColor(current_pixel, 0, 0, 0);
  pixels.show();  // without show there will be no update
  delay(1000);
}