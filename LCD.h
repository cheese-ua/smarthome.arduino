#ifndef SHLCD
#include <LiquidCrystal_I2C.h>
#include "CheeseLog.h"
#include "Cooler.h"
#include "CheeseDHT.h"
#include <DS1302.h>
class LCD {
  private:
    long counter;
    CheeseLog* logger;
    DS1302* rtc;
    Cooler *cooler;
    String BriefTemp(CheeseDHT *dht, String Name);
    CheeseDHT *dhtUp;
    CheeseDHT *dhtDown;
  public:
    LCD(Cooler *cooler, DS1302* rtc, CheeseDHT *dhtUp, CheeseDHT *dhtDown, CheeseLog* logger);
    void Update();
    void PrintText(String txt);
};
#define SHLCD
#endif
