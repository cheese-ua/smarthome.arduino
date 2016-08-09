#include "CheeseUtilites.h"

String CheeseUtilites::GetTimeFromStart_String() {
  CheeseTimeInfo tm = CheeseUtilites::GetTimeFromStart_Struct();
  return String(tm.day)+":"+String(tm.hour)+":"+String(tm.minute)+":"+String(tm.seconds);
}

CheeseTimeInfo CheeseUtilites::GetTimeFromStart_Struct() {
  const int msecSec = 1000;
  const int msecMin = 60 * msecSec;
  const int msecHour = msecMin * 60;
  const int msecDay = msecHour * 24;

  int miliseconds = millis();

  int day = miliseconds / msecDay;
  miliseconds -= day * msecDay;

  int hour = miliseconds / msecHour;
  miliseconds -= hour * msecHour;

  int minute = miliseconds / msecMin;
  miliseconds -= minute * msecMin;

  int seconds = miliseconds / msecSec;
  miliseconds -= seconds * msecSec;

  return {day, hour, minute, seconds, miliseconds};
}




