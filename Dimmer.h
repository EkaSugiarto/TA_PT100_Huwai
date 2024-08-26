#include "esp32-hal-gpio.h"

// Define pins
const int heaterPin = 21;  // pin for heater
const int coolerPin = 19;  // pin for cooler
const int fanPin = 32;     // pin for fan

unsigned long previousMillis = 0;  // will store last time the heater/cooler was updated
const long interval = 500;         // interval at which to turn on/off (milliseconds)

const int tempSetPoint = 50;  // Desired temperature

enum State {
  HEATING,
  COOLING,
  STANDBY
};

State currentState = STANDBY;

void heater() {
  digitalWrite(heaterPin, HIGH);
  digitalWrite(coolerPin, LOW);
  digitalWrite(fanPin, LOW);
  Serial.println("Heater nyala, cooler mati");
  Serial.println(String(Suhu1) + "  " + String(Suhu2) + "\n\n");
}

void cooler() {
  digitalWrite(heaterPin, LOW);
  digitalWrite(coolerPin, HIGH);
  digitalWrite(fanPin, HIGH);
  Serial.println("Heater mati, cooler nyala");
  Serial.println(String(Suhu1) + "  " + String(Suhu2) + "\n\n");
}

void standby() {
  digitalWrite(heaterPin, LOW);
  digitalWrite(coolerPin, LOW);
  digitalWrite(fanPin, LOW);
  Serial.println("Standby ... Heater dan cooler mati");
  Serial.println(String(Suhu1) + "  " + String(Suhu2) + "\n\n");
}

void DimmerS() {
  pinMode(heaterPin, OUTPUT);
  pinMode(coolerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
}

void DimmerL() {
  unsigned long currentMillis = millis();

  MAXL();
  float currentTemperature = Suhu1;

  switch (currentState) {
    case HEATING:
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        standby();
        if (currentTemperature < tempSetPoint) {
          currentState = HEATING;
          heater();
        } else {
          currentState = COOLING;
        }
      }
      break;

    case COOLING:
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        standby();
        if (currentTemperature > tempSetPoint) {
          currentState = COOLING;
          cooler();
        } else {
          currentState = HEATING;
        }
      }
      break;

    case STANDBY:
    default:
      if (currentTemperature < tempSetPoint) {
        currentState = HEATING;
        previousMillis = currentMillis;
        heater();
      } else if (currentTemperature > tempSetPoint) {
        currentState = COOLING;
        previousMillis = currentMillis;
        cooler();
      }
      break;
  }
}