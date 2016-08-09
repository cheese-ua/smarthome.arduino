#ifndef CHEESEDHT
#include "Arduino.h"
#include "DHT.h"
struct ResponseDHT {
  int temperature;
  int humidity;
  int heat_index;
  String date;
};


class CheeseDHT {
  private:
    DHT *dht;
    ResponseDHT respPrevious;
  public:
    int pin;
    String name;
    CheeseDHT(int pin, String name);
    ResponseDHT get();
    static bool IsValidResponse(ResponseDHT resp);
    String toJSON();
};
#define CHEESEDHT
#endif
