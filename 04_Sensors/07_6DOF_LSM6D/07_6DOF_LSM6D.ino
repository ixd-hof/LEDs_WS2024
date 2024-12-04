#include <Adafruit_LSM6DSOX.h>
#include <Adafruit_NeoPixel.h>

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

Adafruit_LSM6DSOX sox;

#define NUMPIXELS 1
//#define PIN_NEOPIXEL     6
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);

  // Neopixel Trinkey
  pixels.begin();            // initialize neopixel(s)
  pixels.setBrightness(50);  // set brightness (0 low, 255 high)
  pixels.fill(pixels.Color(0, 0, 0));
  pixels.show();  // show pixels (necessary!)

  // wait until serial port opens for native USB devices
  //while (!Serial) {
  //  delay(1);
  //}

  // VL53L0X ToF
  if (!sox.begin_I2C()) {
    while (1) {
      delay(10);
    }
  }
  Serial.println("LSM6DSOX Found!");

  // sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
}

void loop() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  int acc_color = map(accel.acceleration.x, -20, 20, -50, 50);
  pixels.fill(Wheel(acc_color));
  pixels.show();

  delay(100);
}





// function wheel: input 0-255 in order to get RGB from color wheel
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
