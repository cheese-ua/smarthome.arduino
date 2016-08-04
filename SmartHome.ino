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
CheeseDHT *dhtUp;
CheeseDHT *dhtDown;
/***********************************************/
void setup() {

  logger = new CheeseLog(&rtc);
  logger->Info("");
  logger->Info("setup: start");
  init_secure();
  dhtUp = new CheeseDHT(0, "UP");
  dhtDown = new CheeseDHT(14, "DOWN");

  cooler = new Cooler(15, &rtc, logger);
  lcd = new LCD(cooler, &rtc, dhtUp, dhtDown, logger);
  lcd->PrintText("Loading...");
  httpStart(cooler, &rtc);
  CheeseWiFi::init(logger);
  logger->Info("setup: end");
  lcd->Update();
}


/***********************************************/
void loop() {
  httpProcess(dhtUp, dhtDown);
  if (++counter % 1001 == 0) {
    cooler->CheckState();
  } else if (++counter % 53 == 0) {
    lcd->Update();
  } else {
    delay(100);
  }
}
