#include <Adafruit_Protomatter.h>
#include "farbverlauf1.h"
#include "farbverlauf2.h"

/* ----------------------------------------------------------------------
The RGB matrix must be wired to VERY SPECIFIC pins, different for each
microcontroller board. This first section sets that up for a number of
supported boards. Notes have been moved to the bottom of the code.
------------------------------------------------------------------------- */

#if defined(_VARIANT_MATRIXPORTAL_M4_)  // MatrixPortal M4
uint8_t rgbPins[] = { 7, 8, 9, 10, 11, 12 };
uint8_t addrPins[] = { 17, 18, 19, 20, 21 };
uint8_t clockPin = 14;
uint8_t latchPin = 15;
uint8_t oePin = 16;
#define BACK_BUTTON 2
#define NEXT_BUTTON 3
#elif defined(ARDUINO_ADAFRUIT_MATRIXPORTAL_ESP32S3)  // MatrixPortal ESP32-S3
uint8_t rgbPins[] = { 42, 41, 40, 38, 39, 37 };
uint8_t addrPins[] = { 45, 36, 48, 35, 21 };
uint8_t clockPin = 2;
uint8_t latchPin = 47;
uint8_t oePin = 14;
#define BACK_BUTTON 6
#define NEXT_BUTTON 7
#endif

Adafruit_Protomatter matrix(
  64,                         // Width of matrix (or matrix chain) in pixels
  4,                          // Bit depth, 1-6
  1, rgbPins,                 // # of matrix chains, array of 6 RGB pins for each
  5, addrPins,                // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin,  // Other matrix control pins
  false);                     // No double-buffering here (see "doublebuffer" example)

// SETUP - RUNS ONCE AT PROGRAM START --------------------------------------

int x = 0;
int buttonstate = 1;

void setup(void) {
  Serial.begin(9600);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if (status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for (;;)
      ;
  }

  matrix.show();  // Copy data to matrix buffers

  // enable buttons
  #if defined(BACK_BUTTON)
    pinMode(BACK_BUTTON, INPUT_PULLUP);
  #endif
  #if defined(NEXT_BUTTON)
    pinMode(NEXT_BUTTON, INPUT_PULLUP);
  #endif
}


void loop(void) {

  // read buttons
  if (!digitalRead(BACK_BUTTON)) {
    buttonstate = 1;
    while (!digitalRead(BACK_BUTTON))
      ;  // Wait for release
  }
  if (!digitalRead(NEXT_BUTTON)) {
    buttonstate = 2;  // Forward
    while (!digitalRead(NEXT_BUTTON))
      ;  // Wait for release
  }

  matrix.fillScreen(0);

  // show image after button press
  if (buttonstate == 1) {
    matrix.drawRGBBitmap(0, 0, farbverlauf1, 128, 32);
    delay(200);
    matrix.drawRGBBitmap(0, 0, farbverlauf2, 128, 32);
    delay(200);
  }
  /*
  else if (buttonstate == 2) {
    matrix.drawRGBBitmap(0, 0, farbverlauf3, 128, 32);
    delay(200);
    matrix.drawRGBBitmap(0, 0, farbverlauf4, 128, 32);
    delay(200);
  }
  */

  matrix.show();  // Copy data to matrix buffers

  // adjust for frame rate
  delay(150);
}