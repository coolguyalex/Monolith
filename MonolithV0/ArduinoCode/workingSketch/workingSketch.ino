#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <BH1750.h>
#include <QMC5883LCompass.h>

// Sensor objects
Adafruit_BME280 bme;          // BME280 environmental sensor
BH1750 lightMeter;            // BH1750 light sensor
QMC5883LCompass mag;          // QMC5883L magnetometer

const int pirPin = 2;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize BME280
  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
  }

  // Initialize BH1750
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 not found!");
  }

  // Initialize QMC5883L
  mag.init();          // NOTE: no return value

  //setup PIR 
  pinMode(pirPin, INPUT);
}

void loop() {
  // Read temperature
  float tempC = bme.readTemperature();
  float Press = bme.readPressure();
  float Humid = bme.readHumidity();

  // Read light level
  float lux = lightMeter.readLightLevel();

  // Read magnetometer
  mag.read();
  int magX = mag.getX();      // choose X-axis only
  int magY = mag.getY();
  int magZ = mag.getZ();

  //Read PIR
  int PIR = digitalRead(pirPin);

  // Print values in a clean PD-friendly packet
  //Serial.print("T "); 
  Serial.print(tempC); Serial.print(" ");
  //Serial.print(", P "); Serial.print(Press);
  //Serial.print(", H "); Serial.print(Humid);
  //Serial.print(" L "); 
  Serial.print(lux);Serial.print(" ");
  //Serial.print(" X "); 
  Serial.print(magX);Serial.print(" ");
  //Serial.print(", Y "); Serial.print(magY);
  //Serial.print(", Z "); Serial.print(magZ);
  //Serial.print(", PIR "); Serial.print(PIR);

  Serial.println();

  delay(50);
}
