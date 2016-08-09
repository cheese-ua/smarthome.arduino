#include <LiquidCrystal_I2C.h>
#ifndef CHEESEUTILITES
#include "CheeseLog.h"

struct CheeseTimeInfo {
  int day;
  int hour;
  int minute;
  int seconds;
  int miliseconds;
};
class CheeseUtilites{
  public:
    static String GetTimeFromStart_String();
    static CheeseTimeInfo GetTimeFromStart_Struct();
};
#define CHEESEUTILITES
#endif
