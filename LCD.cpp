#include "LCD.h"
#include "CheeseDHT11.h"
#include <Wire.h>

LiquidCrystal_I2C currentLCD(0x27, 16, 2);

LCD::LCD(Cooler *cooler, DS1302* rtc, CheeseLog* logger) {
  this->cooler = cooler;
  this->rtc = rtc;
  this->logger = logger;

  Wire.begin(4, 5);
  currentLCD.init();
  currentLCD.backlight();
}

String LCD::BriefTemp(int pin, String Name) {
  ResponseDHT11 t = CheeseDHT11::get(0);
  if (t.temperature < 0) {
    return Name + ": ERR  ";
  }
  String res = Name + ":" + String(t.temperature, DEC) + "#" + String(t.humidity, DEC);
  while (res.length() < 8)
    res += " ";
  return res;
}

void LCD::Update() {
  currentLCD.setCursor(0, 0);
  String line1 = BriefTemp(0, "G") + BriefTemp(14, "C");
  currentLCD.print(line1);

  String strCooler = "CL: " + String(cooler->IsWorking() ? "ON" : "OFF");
  String strLigth = "LT: " + String(false ? "ON" : "OFF");
  String line2 = strCooler+" "+strLigth;
  while (line2.length() < 16)
    line2 += " ";
  currentLCD.setCursor(0, 1);
  currentLCD.print(line2);
}
void LCD::PrintText(String txt){
  currentLCD.setCursor(0, 0);
  currentLCD.print(txt);
}

