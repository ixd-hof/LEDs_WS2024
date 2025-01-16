#include <Adafruit_NeoPixel.h>

// https://wiki.dfrobot.com/Gravity__Analog_Sound_Level_Meter_SKU_SEN0232
#define SoundSensorPin A1  //this pin read the analog voltage from the sound level meter
#define VREF  5.0  //voltage on AREF pin,default:operating voltage

Adafruit_NeoPixel pixels(1, D4, NEO_GRB + NEO_KHZ800); // onboard neopixel Scorpio


void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(255, 0, 100));
  pixels.show();
  delay(1000);
}

void loop() {
  pixels.clear();

  // read the value from the sensor:
  float voltageValue,dbValue;
  voltageValue = analogRead(SoundSensorPin) / 1024.0 * VREF;
  dbValue = voltageValue * 50.0;  //convert voltage to decibel value
  Serial.print(dbValue,1);
  Serial.println(" dBA");

  int dBColor = map(dbValue, 30, 130, 90, 0); // red to green in color wheel

  pixels.setPixelColor(0, pixels.Color(Wheel(dBColor), 0, 0));
  pixels.show();

  delay(50);
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