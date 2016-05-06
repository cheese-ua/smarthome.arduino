#ifndef COOLER
#include "CheeseLog.h"
struct OneTime {
  int hour;
  int minute;
};
struct Schedule {
  OneTime from;
  OneTime to;
};

class Cooler {
  private:
    bool isWorking;
    int pin;
    Schedule* schedules;
    int length;
    CheeseLog* logger;
  public:
    Cooler(int pin, Schedule* schedules, int length, CheeseLog* logger);
    void CheckState();
    void Start();
    void Stop();
    bool IsWorking();
};

#define COOLER
#endif
