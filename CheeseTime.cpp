#include "CheeseTime.h"
DS1302* CheeseTime::rtc = new DS1302(13, 12, 16);

String CheeseTime::Current() {
  return rtc->getDateStr() + String(" ") + rtc->getTimeStr();
}

Time CheeseTime::getTime() {
  return rtc->getTime();
}

String CheeseTime::DayOfWeek(){
  return rtc->getDOWStr();
}

