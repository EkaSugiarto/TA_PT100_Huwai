#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP32Time.h>

#define wifi_ssid "Autecal"
#define wifi_pass "00000000"
#define DHOSTNAME "AuTeCal"

const char* ca_cert = "";

StaticJsonDocument<2000> json_web;

WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP, "pool.ntp.org", 25200, 3600);
ESP32Time rtc(0);

String tanggal_waktu() {
  String string_month, string_day, string_hour, string_minute;
  if (rtc.getMonth() + 1 < 10) string_month = "0" + String(rtc.getMonth() + 1);
  else string_month = String(rtc.getMonth() + 1);
  if (rtc.getDay() < 10) string_day = "0" + String(rtc.getDay());
  else string_day = String(rtc.getDay());

  return String(rtc.getYear()) + "-" + string_month + "-" + string_day + " " + String(rtc.getTime());
}

void WebS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pass);

  Serial.print("Connecting to: ");
  Serial.println(wifi_ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");

  ntp.begin();
  ntp.update();
  rtc.setTime(ntp.getEpochTime());
}

void WebL() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure* client = new WiFiClientSecure;
    client->setInsecure();
    HTTPClient https;

    if (https.begin(*client, "https://autecalibration.iot4environment.com/insert_data.php")) {
      https.addHeader("Content-Type", "application/json");
      String jsonData;

      json_web["suhu1"] = String(kalibrasiSuhu1);
      json_web["suhu2"] = String(Suhu2);
      json_web["tanggal"] = tanggal_waktu();

      serializeJson(json_web, jsonData);

      Serial.println("Start POST...");
      Serial.println(jsonData);

      int httpCode = https.POST(jsonData);

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
          Serial.println("Data sent! Code: " + String(httpCode));
        } else {
          Serial.println("POST failed! Code: " + String(httpCode));
        }
      } else {
        Serial.println("HTTP POST failed! Error: " + https.errorToString(httpCode));
      }

      https.end();
    } else {
      Serial.println("Unable to connect to the server.");
    }
  } else {
    Serial.println("WiFi not connected!");
  }
  json_web.clear();
}