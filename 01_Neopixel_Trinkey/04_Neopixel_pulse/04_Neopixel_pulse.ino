#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)
//#define PIN_NEOPIXEL     6  // for emulator or Pico

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(255, 0, 100) );    // set pixel color (RGB magenta)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  pixels.fill( pixels.Color(255, 0, 100) );    // set color
  int s = sin( millis()/1000.0 ) * 1000; // change /1000.0 for change speed
  int b = map( s, -1000, 1000, 0, 255 );  // mapping sinus pulse -1000>1000 -> to 0>255
  pixels.setBrightness( b ); // set a number from 10 to 255 for brightness
  pixels.show();            // without show there will be no update
}
