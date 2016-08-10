#ifndef CHEESEWIFI

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "CheeseLog.h"

class CheeseWiFi {
  public:
    static char* ssid ;
    static char* password ;
    static void init(CheeseLog* logger);
    static void check(CheeseLog* logger);
};
#define CHEESEWIFI
#endif

