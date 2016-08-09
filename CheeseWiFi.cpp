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
    if (++cnt % 50 != 0)
      logger->InfoNoLine(".");
    else
      logger->Info("");
  }
  logger->Info("");
  logger->Info("init_wifi: ok");

  char* buffer = new char[15];
  IPAddress ip = WiFi.localIP();
  sprintf(buffer, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  logger->Info("Our IP: " + String(buffer));
  logger->Info("init_wifi: end");
}

void CheeseWiFi::check(CheeseLog* logger) {
  int status = WiFi.status();
  logger->Info("WiFi status: " + String(status));
  if (status == WL_CONNECTED)
    return ;
  logger->Info("WiFi restat ");
  WiFi.reconnect();
}
