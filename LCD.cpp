#include "LCD.h"
#include <Wire.h>

LiquidCrystal_I2C currentLCD(0x27, 16, 2);

LCD::LCD(Cooler *cooler, DS1302* rtc, CheeseDHT *dhtUp, CheeseDHT *dhtDown, CheeseLog* logger) {
  this->cooler = cooler;
  this->rtc = rtc;
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
  logger->Info("LCD update");
  if ((++counter) % 3 != 0) {
    currentLCD.setCursor(0, 0);
    String line1 = BriefTemp(dhtUp, "G") + BriefTemp(dhtDown, "C");
    currentLCD.print(line1);

    String line2 = "COOLER: " + String(cooler->IsWorking() ? "ON" : "OFF");
    while (line2.length() < 16)
      line2 += " ";
    currentLCD.setCursor(0, 1);
    currentLCD.print(line2);
  } else {
    String line1 = rtc->getDOWStr();
    while (line1.length() < 16)
      line1 += " ";
    currentLCD.setCursor(0, 0);
    currentLCD.print(line1);

    String line2 = rtc->getDateStr() + String(" ") + rtc->getTimeStr();
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

