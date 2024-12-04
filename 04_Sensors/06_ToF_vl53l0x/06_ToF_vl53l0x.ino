#include "Adafruit_VL53L0X.h"
#include <Adafruit_NeoPixel.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define NUMPIXELS        1
//#define PIN_NEOPIXEL     6
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);

  // Neopixel Trinkey
  pixels.begin();           // initialize neopixel(s)
  pixels.setBrightness(50); // set brightness (0 low, 255 high)
  pixels.fill( pixels.Color(0, 0, 0) );
  pixels.show();            // show pixels (necessary!)

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  // VL53L0X ToF
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    if (measure.RangeMilliMeter < 1200) { // filter out error measurements
      int distance_color = map(measure.RangeMilliMeter, 0, 1200, 100, 0);
      pixels.fill( Wheel(distance_color) );
      pixels.show();
    }

    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
    //Serial.print("\t");
    //Serial.println(brightness);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);
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
