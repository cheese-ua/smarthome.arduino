#ifndef CHEESEDHT11

#include <SimpleDHT.h>
struct ResponseDHT11 {
  int temperature;
  int humidity;
};


class CheeseDHT11 {
  public:
    static SimpleDHT11 dht11;
    static ResponseDHT11 get(int pin);
    static String toJSON(int pin, String name);
};
#define CHEESEDHT11
#endif
