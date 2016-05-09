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
    bool isManualStarted;
    long startMillis;
    String startDate;
    bool IsNeedWorking();
    String ScheduleInfo(Schedule s);
    Schedule CreateSchedule(int hourFrom, int minuteFrom, int hourTo, int minuteTo);
  public:
    Cooler(int pin, DS1302* rtc, CheeseLog* logger);
    void CheckState();
    void Start(bool isManual);
    void Stop();
    bool IsWorking();
    String toJSON();
};

#define COOLER
#endif
