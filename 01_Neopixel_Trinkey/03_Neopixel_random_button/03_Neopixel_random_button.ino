#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1  // number of neopixels (single)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(115200);     // init debug console

  pinMode(PIN_SWITCH, INPUT_PULLUP);

  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(20); // set brightness (0 low, 255 high)
  pixels.fill(0xFFFFFF);    // set pixel color (HEX white)
  pixels.show();            // show pixels (necessary!)
}

void loop() {
  bool curr_button = !digitalRead(PIN_SWITCH);  // read button state: 1 or 0?
  //Serial.println(curr_button);                // debug button state

  if (curr_button == 1) {                       // if button is pressed
    pixels.setPixelColor(0, random(255), random(255), random(255)); // set pixel (0) color to a random RGB value
    pixels.show();
    delay(200);
  }

}
