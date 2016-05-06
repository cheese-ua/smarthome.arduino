#include <LiquidCrystal_I2C.h>
#ifndef CHEESEUTILITES
#include "CheeseLog.h"
#include "CheeseDHT11.h"
struct CheeseTime {
  int day;
  int hour;
  int minute;
  int seconds;
  int miliseconds;
};
class CheeseUtilites{
  public:
    static String GetTimeFromStart_String();
    static CheeseTime GetTimeFromStart_Struct();
    static void PrintDHT11ToLCD16(LiquidCrystal_I2C lcd, int pin, int line, CheeseLog* logger);
};
#define CHEESEUTILITES
#endif
