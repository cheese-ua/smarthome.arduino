#include "secure.h"
#include "CheeseLog.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "HTTPProcessor.h"
#include "Cooler.h"
#include "LCD.h"

CheeseLog* logger;
long counter = 0;
Cooler *cooler;
LCD *lcd;

CheeseDHT *dhtUp;
CheeseDHT *dhtDown;
long secPrevLCD = 0;
long secPrevCooler = 0;
/***********************************************/
void setup() {

  logger = new CheeseLog();
  logger->Info("");
  logger->Info("setup: start");
  init_secure();
  dhtUp = new CheeseDHT(2, "UP");
  dhtDown = new CheeseDHT(14, "DOWN");

  cooler = new Cooler(15, logger);
  lcd = new LCD(cooler, dhtUp, dhtDown, logger);
  lcd->PrintText("Loading...");
  httpStart(cooler);
  CheeseWiFi::init(logger);
  logger->Info("setup: end");
  lcd->Update();
  secPrevLCD = millis() / 1000;
  secPrevCooler = millis() / 1000;
}


/***********************************************/
void loop() {

  httpProcess(dhtUp, dhtDown);

  long secCurrLCD = millis() / 1000;
  long secCurrCooler = millis() / 1000;

  if (secCurrLCD - secPrevLCD > 3)  {
    lcd->Update();
    secPrevLCD = secCurrLCD;
  }

  if (secCurrCooler - secPrevCooler > 30)  {
    cooler->CheckState();
    secPrevCooler = secCurrCooler;
    CheeseWiFi::check(logger);
  }


  delay(100);
}
