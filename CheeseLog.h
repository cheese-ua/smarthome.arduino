#ifndef CHEESELOG
#include "Arduino.h"
class CheeseLog{
  public:
    void Info(String line);
    void InfoNoLine(String line);
};
#define CHEESELOG
#endif
