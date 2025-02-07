#include <seesaw_neopixel.h>

#define NUMPIXELS 24      // number of neopixels
#define PIN_NEODRIVER 15  // Neodriver pin

//seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
}

int w = 0;

void loop() {
  pixels.clear();

  float s = sin(millis() / 1000.0) * 1000.0;
  int w = map(s, -1000, 1000, 0, 255);

  for (int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, Wheel(w));  // insert HSB value generated gy function Wheel()
  }

  pixels.show();            // without show there will be no update

  //delay(200);               // set speed / slowdown
}


// function wheel: input 0-255 in order to get RGB from color wheel
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}