#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Binair.h>

#define WLAN_SSID "yourSSID"
#define WLAN_PASS "yourPass"


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection error");
  }

  BINAIR("[vendor]", "[product]", "[token]", "[platform]", "[version]");
}

void loop() {
  Binair.check();
}
