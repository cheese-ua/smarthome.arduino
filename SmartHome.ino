#include "secure.h"
#include "CheeseLog.h"
#include <Wire.h>
#include "CheeseDHT11.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "HTTPProcessor.h"
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include "Cooler.h"
#include <DS1302.h>

CheeseLog* logger;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(13, 12, 16);
long counter = 0;
Cooler *cooler;

/***********************************************/
void setup() {
  logger = new CheeseLog(&rtc);

  init_secure();

  logger->Info("");
  logger->Info("setup: start");

  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();

  OneTime tf1 = {11, 42};
  OneTime tt1 = {11, 43};
  Schedule s1 = {tf1, tt1};

  OneTime tf2 = {11, 50};
  OneTime tt2 = {11, 51};
  Schedule s2 = {tf2, tt2};

  int length = 2;
  Schedule* schedules = new Schedule[length];
  schedules[0] = s1;
  schedules[1] = s2;
  cooler = new Cooler(15, schedules, length, &rtc, logger);

  httpStart(cooler, &rtc);
  CheeseWiFi::init(logger);

}


/***********************************************/
void loop() {
  httpProcess();
  if (++counter % 100 == 0) {
    logger->Info("");
    logger->Info("LCD update");
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 0, 0, logger);
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 14, 1, logger);
    cooler->CheckState();
    delay(500);
  } else {
    delay(50);
  }
}
