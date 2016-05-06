#include "CheeseUtilites.h"

String CheeseUtilites::GetTimeFromStart_String() {
  CheeseTime tm = CheeseUtilites::GetTimeFromStart_Struct();
  return String(tm.day)+":"+String(tm.hour)+":"+String(tm.minute)+":"+String(tm.seconds);
}

CheeseTime CheeseUtilites::GetTimeFromStart_Struct() {
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


void CheeseUtilites::PrintDHT11ToLCD16(LiquidCrystal_I2C lcd, int pin, int line, CheeseLog* logger) {
  ResponseDHT11 resp = CheeseDHT11::get(pin);

  if (resp.temperature < 0) {
    lcd.setCursor(0, line);
    String lineUp = "t: Err    h: Err";
    lcd.print(lineUp);
    return;
  }

  lcd.setCursor(0, line);
  String lineUp = "t: " + String(resp.temperature, DEC) + "C    h: " + String(resp.humidity, DEC) + "%";
  lcd.print(lineUp);
  logger->Info(lineUp);
}


