#ifndef CHEESELOG
#include "Arduino.h"
#include <DS1302.h>
class CheeseLog{
  private:
    DS1302* rtc;
  public:
    CheeseLog(DS1302* rtc);  
    void Info(String line);
    void InfoNoLine(String line);
};
#define CHEESELOG
#endif
