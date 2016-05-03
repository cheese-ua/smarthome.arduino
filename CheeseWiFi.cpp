#include <ESP8266WiFi.h>
#include "CheeseWiFi.h"

char* CheeseWiFi::ssid = "login";
char* CheeseWiFi::password = "pass";

void CheeseWiFi::init() {
  Serial.println("\n");
  Serial.println("init_wifi: start with login "+String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("Our IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("init_wifi: end");
}
