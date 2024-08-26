#include "esp32-hal-gpio.h"

// Define pins
const int heaterPin = 21;  // pin for heater
const int coolerPin = 19;  // pin for cooler
const int fanPin = 32;     // pin for fan

String pesan;

unsigned long previousMillisssss = 0;  // will store last time the heater/cooler was updated

const long heaterInterval = 50;     // Heater on duration (milliseconds)
const long standbyInterval = 1000;  // Standby duration (milliseconds)
const long coolerInterval = 10000;  // Cooler on duration (milliseconds)

const int tempSetPoint = 50;  // Desired temperature
const int hysteresis = 3;    // Temperature buffer to avoid oscillation

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

  pesan = "Heater on, cooler off";
}

void cooler() {
  digitalWrite(heaterPin, LOW);
  digitalWrite(coolerPin, HIGH);
  digitalWrite(fanPin, HIGH);
  pesan = "Heater off, cooler on";
}

void standby() {
  digitalWrite(heaterPin, LOW);
  digitalWrite(coolerPin, LOW);
  digitalWrite(fanPin, LOW);
  pesan = "Standby ... Heater and cooler off";
}

void DimmerS() {
  pinMode(heaterPin, OUTPUT);
  pinMode(coolerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
}

void DimmerL() {
  MAXL();

  unsigned long currentMillis = millis();

  float currentTemperature = kalibrasiSuhu1;

  switch (currentState) {
    case HEATING:
      if (currentMillis - previousMillisssss >= heaterInterval) {
        previousMillisssss = currentMillis;
        standby();
        currentState = STANDBY;
      }
      break;

    case COOLING:
      if (currentMillis - previousMillisssss >= coolerInterval) {
        previousMillisssss = currentMillis;
        standby();
        currentState = STANDBY;
      }
      break;

    case STANDBY:
    default:
      if (currentMillis - previousMillisssss >= standbyInterval) {
        previousMillisssss = currentMillis;

        if (currentTemperature > (tempSetPoint - hysteresis)) {
          currentState = COOLING;
          cooler();
        } else {
          heater();
        }
      }
      break;
  }
}
