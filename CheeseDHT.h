/*
DHT 11-22
Connect pin 1 (on the left) of the sensor to +5V
NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1 to 3.3V instead of 5V!
Connect pin 2 of the sensor to whatever your DHTPIN is
Connect pin 4 (on the right) of the sensor to GROUND
Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
*/

#ifndef CHEESEDHT
#include "Arduino.h"
#include "DHT.h"

struct ResponseDHT {
  int temperature;
  int humidity;
  String date;
  long millis;
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
