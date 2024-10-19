#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>
#include "Mouse.h"

#define PIN_NEO_ROTARY   6
#define SEESAW_ADDR      0x36

Adafruit_seesaw ss;
seesaw_NeoPixel pixels = seesaw_NeoPixel(1, PIN_NEO_ROTARY, NEO_GRB + NEO_KHZ800);

int32_t encoder_position;
int32_t last_position;

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
  int16_t new_position = ss.getEncoderPosition();   // get encoder current position: -int > +int
  Mouse.move(0, 0, new_position-last_position);     // scroll virtual mouse by moved angle
  Serial.println(new_position-last_position);       // print current position to console
  last_position = new_position;                     // set last position to calculate movement at next iteration
  

  delay(10);
}