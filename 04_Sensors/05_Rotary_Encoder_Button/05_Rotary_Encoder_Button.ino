#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#define PIN_NEO_ROTARY   6
#define SEESAW_ADDR      0x36
#define SS_SWITCH        24

Adafruit_seesaw ss;
seesaw_NeoPixel pixels = seesaw_NeoPixel(1, PIN_NEO_ROTARY, NEO_GRB + NEO_KHZ800);

int32_t encoder_position;
uint32_t fixed_color;

void setup() {
  Serial.begin(9600);                      // enable serial console
  
  ss.begin(SEESAW_ADDR);                   // initialise encoder
  delay(100);
  pixels.begin(SEESAW_ADDR);               // initialize neopixel on encoder board
  pixels.setBrightness(20);                // set brightness (0 low, 100 high)
  pixels.show();

  encoder_position = ss.getEncoderPosition(); // get encoder start position

  ss.pinMode(SS_SWITCH, INPUT_PULLUP);  // use a pin for the built in encoder switch

  Serial.println("Turning on interrupts");
  delay(10);
  ss.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);
  ss.enableEncoderInterrupt();

  fixed_color = pixels.Color(0, 0, 0);
}

void loop() {

  if (! ss.digitalRead(SS_SWITCH)) {
    Serial.println("Button pressed!");
    fixed_color = pixels.Color(random(255), random(255), random(255));
    pixels.setPixelColor(0, fixed_color);
  }

  int16_t new_position = ss.getEncoderPosition(); // get encoder current position: -int > +int
  Serial.println(new_position);                // print current id to console
  
  //pixels.setPixelColor(0, fixed_color); // set color wheel, & 0xFF limits to 0-255
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