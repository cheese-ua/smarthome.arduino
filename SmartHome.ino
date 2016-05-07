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
  
  Schedule schedules[] = { {{10,10}, {10, 20}} };
  cooler = new Cooler(15, schedules, 1, logger);

  httpStart(cooler);
  CheeseWiFi::init(logger);

}


/***********************************************/
void loop() {
  httpProcess();

  if (++counter % 100 == 0) {
    logger->Info("LCD update");
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 0, 0, logger);
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 14, 1, logger);
    delay(500);
  } else {
    delay(50);
  }
}
