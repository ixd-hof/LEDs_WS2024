#include <seesaw_neopixel.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "bitmap.h"
#include "bitmap2.h"
#include "pattern_arrow.h"
// Convert bitmaps here: https://notisrac.github.io/FileToCArray/

#define WIDTH 8
#define HEIGHT 32
#define NUMPIXELS WIDTH* HEIGHT  // number of neopixels
#define PIN_NEODRIVER 15         // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);
GFXcanvas16 canvas = GFXcanvas16(WIDTH, HEIGHT);
String type = "progressive";  // matrix type (8x8 progressive or 32x8 zigzag)

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
  canvas.fillScreen(Color(0, 0, 0));
  //canvas.drawGrayscaleBitmap(0, 0, MattSmith_32x8, 8, 32);
  //canvas.drawGrayscaleBitmap(0, 0, Pattern, 8, 32);
  canvas.drawRGBBitmap(0, 0, pattern_arrow, 8, 8);
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
      uint16_t pos;
      if (type == "progressive")
        pos = x + WIDTH * y;
      else {
        if (y % 2 == 0)
          pos = (WIDTH - 1 - x) + WIDTH * y;
        else
          pos = x + WIDTH * y;
      }
      pixels.setPixelColor(pos, ((px >> 11) & 0x1F), ((px >> 5) & 0x3F), (px & 0x1F));
    }
  }
}

uint16_t Color(uint8_t red, uint8_t green, uint8_t blue) {
  red >>= 3;
  green >>= 2;
  blue >>= 3;
  return (red << 11) | (green << 5) | blue;
}