#include "ThingSpeak.h"
#include <HTTPClient.h>

unsigned long myChannelNumber = 3;
const char* myWriteAPIKey = "4DMWAZ6ANR3UTGNK";

WiFiClient client2;

int x;

void TSS() {
  
  ThingSpeak.begin(client2);
}

void TSL() {
  ThingSpeak.setField(1, kalibrasiSuhu1);
  // ThingSpeak.setField(2, Suhu1);
  ThingSpeak.setField(2, Suhu2);
  
  x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
  Serial.println("Channel update successful.");
  }
  else {
  Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}