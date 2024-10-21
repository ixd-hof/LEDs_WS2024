#include <seesaw_neopixel.h>

#define NUMPIXELS 24      // number of neopixels
#define PIN_NEODRIVER 15  // Neodriver pin

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

  // colors:
  // 100%: 255, 0, 100
  // 75%: 191, 0, 80
  // 50%: 128, 0, 51
  // 25%: 64, 0, 26
  // 12.5% 32, 0, 12

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0);  // set other pixels to black
  }

  // %NUMPIXELS: Modulo of 24. Clamps a continuous number to 0-24 and jumping correct over 0
  pixels.setPixelColor(current_pixel % NUMPIXELS, 255, 0, 100);
  pixels.setPixelColor((current_pixel-1) % NUMPIXELS, 191, 0, 80);
  pixels.setPixelColor((current_pixel-2) % NUMPIXELS, 128, 0, 51);
  pixels.setPixelColor((current_pixel-3) % NUMPIXELS, 32, 0, 12);

  /*
  Serial.print(current_pixel);
  Serial.print(" ");
  Serial.print(current_pixel % 24);
  Serial.print(" ");
  Serial.print((current_pixel-1) % 24);
  Serial.print(" ");
  Serial.print((current_pixel-2) % 24);
  Serial.print(" ");
  Serial.println((current_pixel-3) % 24);
  */

  pixels.show();  // without show there will be no update
  current_pixel += 1;
  delay(100);               // set speed / slowdown
}