#include "CheeseWiFi.h"

char* CheeseWiFi::ssid = "login";
char* CheeseWiFi::password = "pass";

void CheeseWiFi::init(CheeseLog* logger) {
  logger->Info("\n");
  logger->Info("init_wifi: start with login " + String(ssid));
  WiFi.begin(ssid, password);
  logger->Info("");
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (++cnt % 100 == 0)
      logger->InfoNoLine("");
    logger->Info("");
  }

  logger->Info("Our IP: "+WiFi.localIP());
  logger->Info("init_wifi: end");
}
