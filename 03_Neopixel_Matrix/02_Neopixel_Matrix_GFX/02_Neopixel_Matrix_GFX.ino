#include <seesaw_neopixel.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define WIDTH 8
#define HEIGHT 8
#define NUMPIXELS WIDTH* HEIGHT  // number of neopixels
#define PIN_NEODRIVER 15         // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);
GFXcanvas16 canvas = GFXcanvas16(WIDTH, HEIGHT);

#define AQUA 0x07FF
#define DEEPPINK 0xF8B2
#define TOMATO 0xFB08 

void setup() {
  Serial.begin();

  // initialize matrix
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
  delay(1000);

  // draw on canvas
  canvas.startWrite();
  canvas.fillCircle(2, 2, 2, Color(0, 0, 255)); // magenta filled circle
  canvas.drawRect(1, 1, 6, 6, Color(255, 70, 0)); // orange rect
  canvas.drawLine(0, 0, 7, 7, Color(0, 0, 255));  // blue diagonal line
  canvas.endWrite();
  // write canvas to matrix
  drawCanvas();

  pixels.show();
}

void loop() {

}


// helper classes
// ignore or be curious
void drawCanvas() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      uint16_t px = canvas.getPixel(x, y);
      //Serial.println(px, HEX);
      pixels.setPixelColor(x + WIDTH * y, (uint16_t)px >> 10, (uint8_t)px >> 5, px);
    }
  }
}

uint16_t Color(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}