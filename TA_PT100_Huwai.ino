#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Max.h"
#include "Dimmer.h"
#include "Webs.h"
#include "TS.h"

unsigned long previousMillis15s = 0;
const unsigned long interval15s = 15000;  // 15 seconds

unsigned long previousMillis1s = 0;
const unsigned long interval1s = 1000;  // 1 second

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  MAXS();
  DimmerS();
  // WebS();
  // TSS();
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis15s >= interval15s) {
    previousMillis15s = currentMillis;
    // TSL();
  }

  DimmerL();
  if (currentMillis - previousMillis1s >= interval1s) {
    Serial.println(String(kalibrasiSuhu1) + " , " + String(Suhu2));
    previousMillis1s = currentMillis;
  }
}