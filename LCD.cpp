#include "LCD.h"
#include <Wire.h>
#include "CheeseTime.h"
LiquidCrystal_I2C currentLCD(0x27, 16, 2);

LCD::LCD(Cooler *cooler, CheeseDHT *dhtUp, CheeseDHT *dhtDown, CheeseLog* logger) {
  this->cooler = cooler;
  this->logger = logger;
  this->dhtUp = dhtUp;
  this->dhtDown = dhtDown;
  Wire.begin(4, 5);
  currentLCD.init();
  currentLCD.backlight();
  counter = 0;
}

String LCD::BriefTemp(CheeseDHT *dht, String Name) {
  ResponseDHT t = dht->get();
  if (!CheeseDHT::IsValidResponse(t)) {
    return Name + ": ERR  ";
  }
  String res = Name + ":" + String(t.temperature, DEC) + "#" + String(t.humidity, DEC);
  while (res.length() < 8)
    res += " ";
  return res;
}

void LCD::Update() {
  if ((++counter) % 2 != 0) {
    logger->Info("LCD update - data");

    currentLCD.setCursor(0, 0);
    String line1 = BriefTemp(dhtUp, "U") + BriefTemp(dhtDown, "D");
    currentLCD.print(line1);

    String line2 = "COOLER: " + String(cooler->IsWorking() ? "ON" : "OFF");
    while (line2.length() < 16)
      line2 += " ";
    currentLCD.setCursor(0, 1);
    currentLCD.print(line2);
  } else {
    logger->Info("LCD update - time");

    String line1 = CheeseTime::DayOfWeek();
    while (line1.length() < 16)
      line1 += " ";
    currentLCD.setCursor(0, 0);
    currentLCD.print(line1);

    String line2 = CheeseTime::Current();
    while (line2.length() < 16)
      line2 += " ";
    currentLCD.setCursor(0, 1);
    currentLCD.print(line2);
  }
}

void LCD::PrintText(String txt) {
  currentLCD.setCursor(0, 0);
  currentLCD.print(txt);
}

