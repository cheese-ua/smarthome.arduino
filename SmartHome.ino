#include <Wire.h>
#include "CheeseDHT11.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "HTTPProcessor.h"
#include "secure.h"
#include "CheeseLog.h"
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include "Cooler.h"

CheeseLog* logger = new CheeseLog();
LiquidCrystal_I2C lcd(0x27, 16, 2);

long counter = 0;
Cooler *cooler;

/***********************************************/
void setup() {
  init_secure();
  Serial.begin(115200);
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
    logger->Info("LCD update: "+CheeseUtilites::GetTimeFromStart());
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 0, 0, logger);
    CheeseUtilites::PrintDHT11ToLCD16(lcd, 14, 1, logger);
    delay(500);
  } else {
    delay(50);
  }
}
