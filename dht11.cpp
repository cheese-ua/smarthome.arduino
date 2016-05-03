/*
 * dht11.cpp
 *
 *  Created on: 2 ��� 2016
 *      Author: cheese
 */

#include <SimpleDHT.h>
#include "dht11.h"

SimpleDHT11 MyDHT11::dht11;

ResponseDHT11 MyDHT11::getTemp(int pin) {
	byte temperature;
	byte humidity;
	byte data[40] = { 0 };
	if (dht11.read(pin, &(temperature), &(humidity), data)){
    ResponseDHT11 resp1 = {-1, -1};
    return resp1;
	}
	ResponseDHT11 resp2 = {(int)temperature, (int)humidity};
  return resp2;
}

