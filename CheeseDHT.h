#ifndef CHEESEDHT
#include "Arduino.h"
#include "DHT.h"
struct ResponseDHT {
  int temperature;
  int humidity;
  int heat_index;
};


class CheeseDHT {
  private:
    DHT *dht;
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
