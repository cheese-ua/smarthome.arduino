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

DS1302 rtc(13, 12, 16); //(rst, dat, clk);
CheeseDHT *dhtUp;
CheeseDHT *dhtDown;
long secPrevLCD=0;
long secPrevCooler=0;
/***********************************************/
void setup() {

  logger = new CheeseLog(&rtc);
  logger->Info("");
  logger->Info("setup: start");
  init_secure();
  dhtUp = new CheeseDHT(2, "UP");
  dhtDown = new CheeseDHT(14, "DOWN");

  cooler = new Cooler(15, &rtc, logger);
  lcd = new LCD(cooler, &rtc, dhtUp, dhtDown, logger);
  lcd->PrintText("Loading...");
  httpStart(cooler, &rtc);
  CheeseWiFi::init(logger);
  logger->Info("setup: end");
  lcd->Update();
  secPrevLCD=millis()/1000;
  secPrevCooler=millis()/1000;
}


/***********************************************/
void loop() {
  
  httpProcess(dhtUp, dhtDown);

  long secCurrLCD=millis()/1000;
  long secCurrCooler=millis()/1000;

  if(secCurrLCD-secPrevLCD>5)  {
    lcd->Update();
    secPrevLCD = secCurrLCD;
  }

  if(secCurrCooler-secPrevCooler>30)  {
    cooler->CheckState();
    secPrevCooler = secCurrCooler;
  }

  delay(100);
}
