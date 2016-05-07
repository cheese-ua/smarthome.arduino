#include "secure.h"
#include "CheeseLog.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "HTTPProcessor.h"
#include "Cooler.h"
#include "LCD.h"
#include <DS1302.h>

CheeseLog* logger;
long counter = 0;
Cooler *cooler;
LCD *lcd;
DS1302 rtc(13, 12, 16);
/***********************************************/
void setup() {

  logger = new CheeseLog(&rtc);
  logger->Info("");
  logger->Info("setup: start");
  init_secure();


  cooler = new Cooler(15, &rtc, logger);
  lcd = new LCD(cooler, &rtc, logger);
  lcd->PrintText("Loading...");
  httpStart(cooler, &rtc);
  CheeseWiFi::init(logger);
  logger->Info("setup: end");
}


/***********************************************/
void loop() {
  httpProcess();
  if (++counter % 100 == 0) {
    logger->Info("");
    lcd->Update();
    cooler->CheckState();
    delay(500);
  } else {
    delay(50);
  }
}
