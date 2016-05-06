#include <ESP8266WiFi.h>
#include "CheeseWiFi.h"

char* CheeseWiFi::ssid = "login";
char* CheeseWiFi::password = "pass";

void CheeseWiFi::init() {
  Serial.println("\n");
  Serial.println("init_wifi: start with login " + String(ssid));
  WiFi.begin(ssid, password);
  Serial.println("");
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (++cnt % 100 == 0)
      Serial.println("");
    Serial.print(".");
  }

  Serial.println("Our IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("init_wifi: end");
}
