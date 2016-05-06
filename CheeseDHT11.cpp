/*
   dht11.cpp

    Created on: 2 ��� 2016
        Author: cheese
*/

#include <SimpleDHT.h>
#include "CheeseDHT11.h"

SimpleDHT11 CheeseDHT11::dht11;

ResponseDHT11 CheeseDHT11::get(int pin) {
  byte temperature;
  byte humidity;
  byte data[40] = { 0 };
  if (dht11.read(pin, &(temperature), &(humidity), data)) {
    ResponseDHT11 resp1 = { -1, -1};
    return resp1;
  }
  ResponseDHT11 resp2 = {(int)temperature, (int)humidity};
  return resp2;
}

String CheeseDHT11::toJSON(int pin, String name) {
  ResponseDHT11 resp = get(pin);
  return resp.temperature < 0
         ? "{\"pin\":" + String(pin) + ",\"name\":\"" + name +  "\",\"error\":\"Read failed\"}"
         : "{\"pin\":" + String(pin) + ",\"name\":\"" +  name +  "\",\"t\":" + String(resp.temperature) + ",\"h\":" + String(resp.humidity) + "}";
}

