#include <ESP8266WiFi.h>
#ifndef MYWIFI
class MyWiFi {
  public:
    MyWiFi();
    static char* ssid ;
    static char* password ;
    static WiFiServer server;
    static void init_wifi();
};
#define MYWIFI
#endif

