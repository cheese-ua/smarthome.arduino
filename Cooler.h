#ifndef COOLER
#include "CheeseLog.h"
#include <DS1302.h>
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
    DS1302* rtc;
    bool isWorking;
    int pin;
    Schedule* schedules;
    int length;
    CheeseLog* logger;
    bool IsNeedWorking();
    String ScheduleInfo(Schedule s);
  public:
    Cooler(int pin, Schedule* schedules, int length, DS1302* rtc, CheeseLog* logger);
    void CheckState();
    void Start();
    void Stop();
    bool IsWorking();
};

#define COOLER
#endif
