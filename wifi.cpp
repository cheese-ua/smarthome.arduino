#include <ESP8266WiFi.h>
#include "wifi.h"

char* MyWiFi::ssid = "login";
char* MyWiFi::password = "pass";

WiFiServer MyWiFi::server(80);

MyWiFi::MyWiFi() {

}
void MyWiFi::init_wifi() {
  Serial.println("\n");
  Serial.println("init_wifi: start with login "+String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  server.begin();
  Serial.println("Our IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("init_wifi: end");
}
