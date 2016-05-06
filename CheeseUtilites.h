#include <LiquidCrystal_I2C.h>
#ifndef CHEESEUTILITES
struct CheeseTime{
  int day;
  int hour;
  int minute;
  int seconds;
  int miliseconds;
};
#define CHEESEUTILITES
#endif

String GetTimeFromStart() {
  const int secHour = 3600;
  const int secMin = 60;
  int seconds = (float) millis() / 1000.0;
  if(seconds>secHour){
    int hour = seconds/secHour;
    seconds-= hour*secHour;
    seconds-= hour*secMin;
    int minute = seconds/secMin;
    seconds-= minute*secMin;
    return String(hour)+"h "+String(minute)+"m "+String(seconds)+"s";
  }else if(seconds>secMin){
    int minute = seconds/secMin;
    seconds-= minute*secMin;
    return String(minute)+"m "+String(seconds)+"s";
  }
    return String(seconds)+"s";
}

CheeseTime GetCheeseTimeFromStart() {
  const int msecSec = 1000;
  const int msecMin = 60*msecSec;
  const int msecHour = msecMin*60;
  const int msecDay = msecHour*24;
  
  int miliseconds = millis();

  int day = miliseconds/msecDay;
  miliseconds -= day*msecDay;

  int hour = miliseconds/msecHour;
  miliseconds-= hour*msecHour;
    
  int minute = miliseconds/msecMin;
  miliseconds-= minute*msecMin;
    
  int seconds = miliseconds/msecSec;
  miliseconds-= seconds*msecSec;

  return {day, hour, minute, seconds, miliseconds};
}


void PrintDHT11ToLCD16(LiquidCrystal_I2C lcd, int pin, int line) {
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
}
