#include "esp32-hal-gpio.h"
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(17, 16, 4, 18);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(26, 27, 14, 33);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF 430.0
// The 'nominal' O-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL 100

float Suhu1, Suhu2;

float calibrateTemperature(float rawTemperature) {
  // Calibration using linear regression: y = mx + c
  float m = 1.04225;  // slope from calibration curve
  float c = 0.08935;  // intercept from calibration curve
  return m * rawTemperature + c;
}

float kalibrasiSuhu1;

void MAXS() {
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  delay(2000);
  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);

  thermo1.begin(MAX31865_3WIRE);
  thermo2.begin(MAX31865_3WIRE);
}

float MAXL() {
  uint16_t rtd1 = thermo1.readRTD();
  float ratio1 = rtd1;
  ratio1 /= 32768;
  Suhu1 = thermo1.temperature(RNOMINAL, RREF);
  // Serial.print("T1 = ");
  // Serial.print(" , ");

  uint16_t rtd2 = thermo2.readRTD();
  float ratio2 = rtd2;
  ratio2 /= 32768;
  Suhu2 = thermo2.temperature(RNOMINAL, RREF);

  // Serial.println();
  kalibrasiSuhu1 = calibrateTemperature(Suhu1);
  return calibrateTemperature(Suhu1);
}

void MAXA() {
  ESP.restart();
  digitalWrite(17, LOW);
  // digitalWrite(16, LOW);
  // digitalWrite(41, LOW);
  digitalWrite(18, HIGH);

  digitalWrite(26, LOW);
  // digitalWrite(27, LOW);
  // digitalWrite(14, LOW);
  digitalWrite(33, HIGH);
}