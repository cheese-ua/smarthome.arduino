#include "CheeseDHT.h"
#include "CheeseUtilites.h"

CheeseDHT::CheeseDHT(int pin, String name) {
  dht = new DHT(pin, DHT22);
  dht->begin();
  this->pin = pin;
  this->name = name;
  respPrevious = {(int)10000, (int)10000, (int)10000, CheeseUtilites::GetTimeFromStart_String()};
}

ResponseDHT CheeseDHT::get() {
  float h = dht->readHumidity();
  delay(250);
  float t = dht->readTemperature();
  delay(250);
  float hic = dht->computeHeatIndex(t, h, false);
  ResponseDHT resp2 = {(int)t, (int)h, (int)hic, CheeseUtilites::GetTimeFromStart_String()};
  if (!IsValidResponse(resp2) && IsValidResponse(respPrevious))
    return respPrevious;
  respPrevious = resp2;
  return resp2;
}
bool CheeseDHT::IsValidResponse(ResponseDHT resp) {
  return !isnan(resp.temperature) && resp.temperature < 500 && !isnan(resp.humidity) && resp.humidity < 500;
}
String CheeseDHT::toJSON() {
  ResponseDHT resp = get();
  return !IsValidResponse(resp)
         ? "{\"pin\":" + String(pin) + ",\"name\":\"" + name +  "\",\"error\":\"Read failed\"}"
         : "{\"pin\":" + String(pin) + ",\"name\":\"" +  name +  "\",\"t\":" + String(resp.temperature) + ",\"h\":" + String(resp.humidity) + ",\"idx\":" + String(resp.heat_index) + ",\"date\":" + resp.date + "}";
}

