#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#ifndef CHEESEWIFI
class CheeseWiFi {
  public:
    static char* ssid ;
    static char* password ;
    static void init();
};
#define CHEESEWIFI
#endif

