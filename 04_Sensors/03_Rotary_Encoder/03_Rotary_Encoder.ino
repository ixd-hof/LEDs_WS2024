#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#define PIN_NEO_ROTARY   6
#define SEESAW_ADDR      0x36

Adafruit_seesaw ss;
seesaw_NeoPixel pixels = seesaw_NeoPixel(1, PIN_NEO_ROTARY, NEO_GRB + NEO_KHZ800);

int32_t encoder_position;

void setup() {
  Serial.begin(9600);                      // enable serial console
  
  ss.begin(SEESAW_ADDR);                   // initialise encoder
  delay(100);
  pixels.begin(SEESAW_ADDR);               // initialize neopixel on encoder board
  pixels.setBrightness(20);                // set brightness (0 low, 100 high)
  pixels.show();

  encoder_position = ss.getEncoderPosition(); // get encoder start position
}

void loop() {
  int16_t new_position = ss.getEncoderPosition(); // get encoder current position: -int > +int
  Serial.println(new_position);                // print current id to console
  
  pixels.setPixelColor(0, Wheel(new_position & 0xFF)); // set color wheel, & 0xFF limits to 0-255
  pixels.show();
  delay(10);
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