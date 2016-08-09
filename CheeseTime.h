#ifndef CHEESETIME
#include "Arduino.h"
#include <DS1302.h>
class CheeseTime {
  private:
    static DS1302* rtc; //(rst, dat, clk);
  public:
    static String Current();
    static Time getTime();
    static String DayOfWeek();
};
#define CHEESETIME
#endif
