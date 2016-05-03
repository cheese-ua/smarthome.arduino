/*
   dht11.cpp

    Created on: 2 ��� 2016
        Author: cheese
*/

#include <SimpleDHT.h>

struct ResponseDHT11 {
  int temperature;
  int humidity;
};


class MyDHT11 {
  public:
    static SimpleDHT11 dht11;
    static ResponseDHT11 getTemp(int pin);
};

