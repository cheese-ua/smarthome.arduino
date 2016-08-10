#include "CheeseDHT.h"
#include "CheeseTime.h"

CheeseDHT::CheeseDHT(int pin, String name) {
  dht = new DHT(pin, DHT22);
  dht->begin();
  this->pin = pin;
  this->name = name;
  respPrevious = {(int)10000, (int)10000, CheeseTime::Current(), millis()};
}

ResponseDHT CheeseDHT::get() {
  delay(100);
  float h = dht->readHumidity();
  delay(100);
  float t = dht->readTemperature();
  ResponseDHT resp2 = {(int)t, (int)h, CheeseTime::Current(), millis()};
  if (!IsValidResponse(resp2) && IsValidResponse(respPrevious))
    return respPrevious;
  respPrevious = resp2;
  return resp2;
}
bool CheeseDHT::IsValidResponse(ResponseDHT resp) {
  return !isnan(resp.temperature) && resp.temperature < 500 && !isnan(resp.humidity) && resp.humidity < 500 && (millis()-resp.millis)<15000;
}
String CheeseDHT::toJSON() {
  ResponseDHT resp = get();
  return !IsValidResponse(resp)
         ? "{\"pin\":" + String(pin) + ",\"name\":\"" + name +  "\",\"error\":\"Read failed\"}"
         : "{\"pin\":" + String(pin) + ",\"name\":\"" +  name +  "\",\"t\":" + String(resp.temperature) + ",\"h\":" + String(resp.humidity) + ",\"date\":" + resp.date + ", \"seconds_ago\":"+String((millis()-resp.millis)/1000)+"}";
}

