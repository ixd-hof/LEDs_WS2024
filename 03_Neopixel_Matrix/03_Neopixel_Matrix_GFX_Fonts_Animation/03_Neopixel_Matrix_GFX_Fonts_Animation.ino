#include <seesaw_neopixel.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Fonts/Picopixel.h>

#define WIDTH 8
#define HEIGHT 8
#define NUMPIXELS WIDTH* HEIGHT  // number of neopixels
#define PIN_NEODRIVER 15         // Neodriver pin

seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);
GFXcanvas16 canvas = GFXcanvas16(WIDTH, HEIGHT);
String type = "zigzag"; // matrix type (8x8 progressive or 32x8 zigzag)

#define AQUA 0x07FF
#define DEEPPINK 0xF8B2
#define TOMATO 0xFB08

// start x scroll position
// increase relative to word length
int x = 12;

void setup() {
  Serial.begin();

  // initialize matrix
  pixels.begin(0x60);        // initialize neopixels with neodriver address
  pixels.setBrightness(20);  // set lower brightness
  pixels.show();
  
  canvas.setFont(&Picopixel);
  canvas.setCursor(x, 5);
  canvas.setTextColor(Color(255, 0, 0));
}

void loop() {

  // draw on canvas
  canvas.startWrite();
  canvas.fillScreen(Color(0,0,0));// fill screen back before redraw
  canvas.setCursor(x, 5);         // set relative x position for scroll effect
  canvas.print("Hello");
  canvas.endWrite();

  // write canvas to matrix
  drawCanvas();
  pixels.show();

  if (x > -15)                    // decrease x position while smaller than -15
    x -= 1;
  else
    x = 12;                       // otherwise set back to 12 and start again
                                  // adapt values in order to fit word length
  delay(100);
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
        if (y%2 == 0)
          pos = (WIDTH-1 - x) + WIDTH * y;
        else
          pos = x + WIDTH * y;
      }
      pixels.setPixelColor(pos, (uint16_t)px >> 10, (uint8_t)px >> 5, px);
    }
  }
}

uint16_t Color(uint8_t red, uint8_t green, uint8_t blue) {
  red >>= 3;
  green >>= 2;
  blue >>= 3;
  return (red << 11) | (green << 5) | blue;
}