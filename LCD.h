#ifndef SHLCD
#include <LiquidCrystal_I2C.h>
#include "CheeseLog.h"
#include "Cooler.h"
#include "CheeseDHT.h"
class LCD {
  private:
    long counter;
    CheeseLog* logger;
    Cooler *cooler;
    String BriefTemp(CheeseDHT *dht, String Name);
    CheeseDHT *dhtUp;
    CheeseDHT *dhtDown;
  public:
    LCD(Cooler *cooler, CheeseDHT *dhtUp, CheeseDHT *dhtDown, CheeseLog* logger);
    void Update();
    void PrintText(String txt);
};
#define SHLCD
#endif
