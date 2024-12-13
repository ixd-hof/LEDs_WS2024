#include <Adafruit_NeoPixel.h>
float filteringFactor = 0.1;
float micFiltered = 0;
int micPeak = 0;

Adafruit_NeoPixel pixels(1, D4, NEO_GRB + NEO_KHZ800); // onboard neopixel Scorpio

int sensorPin = A1;   // select the input pin for the potentiometer
int micValue = 0;  // variable to store the value coming from the sensor

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
  micValue = analogRead(sensorPin);
  micFiltered = micValue * filteringFactor + micFiltered * (1.0 - filteringFactor);

  if (micValue > micFiltered)
    micPeak = micValue - micFiltered;
  Serial.print(micValue);
  Serial.print(",");
  Serial.print(micFiltered);
  Serial.print(",");
  Serial.println(micPeak);

  pixels.setPixelColor(0, pixels.Color(micPeak, 0, 0));
  pixels.show();

  delay(50);
}
