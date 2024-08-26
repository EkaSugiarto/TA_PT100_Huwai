#include "esp32-hal-gpio.h"

// Define pins
const int heaterPin = 21;  // pin for heater
const int coolerPin = 19;  // pin for cooler
const int fanPin = 32;     // pin for fan

unsigned long previousMillisssss = 0;  // will store last time the heater/cooler was updated

const long heaterInterval = 100;   // Heater on duration (milliseconds)
const long standbyInterval = 1000; // Standby duration (milliseconds)
const long coolerInterval = 2000;  // Cooler on duration (milliseconds)

const int tempSetPoint = 50;       // Desired temperature

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
  MAXL();

  unsigned long currentMillis = millis();

  // Read the current temperature from the sensor (update currentTemperature)
  float currentTemperature = Suhu1;

  switch (currentState) {
    case HEATING:
      if (currentMillis - previousMillisssss >= heaterInterval) {
        previousMillisssss = currentMillis;
        standby();  // Turn off heater and cooler
        currentState = STANDBY;
      }
      break;

    case COOLING:
      if (currentMillis - previousMillisssss >= coolerInterval) {
        previousMillisssss = currentMillis;
        standby();  // Turn off heater and cooler
        currentState = STANDBY;
      }
      break;

    case STANDBY:
    default:
      if (currentMillis - previousMillisssss >= standbyInterval) {
        previousMillisssss = currentMillis;
        if (currentTemperature < tempSetPoint) {
          currentState = HEATING;
          heater();  // Turn on heater for 100 ms
        } else if (currentTemperature > tempSetPoint) {
          currentState = COOLING;
          cooler();  // Turn on cooler for 2000 ms
        }
      }
      break;
  }


  // unsigned long currentMillis = millis();

  // float currentTemperature = Suhu1;

  // switch (currentState) {
  //   case HEATING:
  //     if (currentMillis - previousMillisssss >= interval) {
  //       previousMillisssss = currentMillis;
  //       standby();
  //       if (currentTemperature < tempSetPoint) {
  //         currentState = HEATING;
  //         heater();
  //       } else {
  //         currentState = COOLING;
  //       }
  //     }
  //     break;

  //   case COOLING:
  //     if (currentMillis - previousMillisssss >= interval) {
  //       previousMillisssss = currentMillis;
  //       standby();
  //       if (currentTemperature > tempSetPoint) {
  //         currentState = COOLING;
  //         cooler();
  //       } else {
  //         currentState = HEATING;
  //       }
  //     }
  //     break;

  //   case STANDBY:
  //   default:
  //     if (currentTemperature < tempSetPoint) {
  //       currentState = HEATING;
  //       previousMillisssss = currentMillis;
  //       heater();
  //     } else if (currentTemperature > tempSetPoint) {
  //       currentState = COOLING;
  //       previousMillisssss = currentMillis;
  //       cooler();
  //     }
  //     break;
  // }
}