#include "Arduino.h"
#include "Cooler.h"

Cooler::Cooler(int pin, DS1302* rtc, CheeseLog* logger) {
  this->pin = pin;
  this->logger = logger;
  pinMode(this->pin, OUTPUT);
  isWorking = false;
  this->rtc = rtc;

  length = 12;
  schedules = new Schedule[length];
  schedules[0] = CreateSchedule(1, 0, 1, 15);
  schedules[1] = CreateSchedule(3, 0, 3, 15);
  schedules[2] = CreateSchedule(5, 0, 5, 15);
  schedules[3] = CreateSchedule(7, 0, 7, 15);
  schedules[4] = CreateSchedule(9, 0, 9, 15);
  schedules[5] = CreateSchedule(11, 0, 11, 15);
  schedules[6] = CreateSchedule(13, 0, 13, 15);
  schedules[7] = CreateSchedule(15, 0, 15, 15);
  schedules[8] = CreateSchedule(17, 0, 17, 15);
  schedules[9] = CreateSchedule(19, 0, 19, 15);
  schedules[10] = CreateSchedule(21, 0, 21, 15);
  schedules[11] = CreateSchedule(23, 0, 21, 15);
  
}
Schedule Cooler::CreateSchedule(int hourFrom, int minuteFrom, int hourTo, int minuteTo) {
  OneTime tf1 = {hourFrom, minuteFrom};
  OneTime tt1 = {hourTo, minuteTo};
  return Schedule{tf1, tt1};
}
void Cooler::CheckState() {
  bool needWork = IsNeedWorking();
  logger->Info("Cooler need work: " + String(needWork));
  if (needWork) {
    if (!isWorking)
      Start(false);
  } else {
    if (isWorking)
      Stop();
  }
  logger->Info("Cooler state: " + String(isWorking));
}

String Cooler::ScheduleInfo(Schedule s) {
  return "from " + String(s.from.hour) + ":" + String(s.from.minute) + " to " + String(s.to.hour) + ":" + String(s.to.minute);
}

bool Cooler::IsNeedWorking() {
  if (isManualStarted) {
    int minutes = (millis() - startMillis) / 60000;
    logger->Info("Manual started: "+String(minutes)+" minutes");
    if (minutes > 30) {
      logger->Info("Manual start timeout");
      return false;
    }
    return true;
  }
  Time t = rtc->getTime();
  logger->Info("Curr hour: " + String(t.hour) + " min: " + String(t.min));
  for (int i = 0; i < length; i++) {
    Schedule s = schedules[i];
    if (s.from.hour <= t.hour && s.from.minute <= t.min && s.to.hour >= t.hour && s.to.minute >= t.min) {
      logger->Info(ScheduleInfo(s) + ": need work");
      return true;
    } else {
      logger->Info(ScheduleInfo(s) + ": don`t need work");
    }
  }
  return false;
}

void Cooler::Start(bool isManual) {
  logger->Info("Cooler started. Manual: " + String(isManual?"yes":"no"));
  digitalWrite(pin, HIGH);
  isWorking = true;
  isManualStarted = isManual;
  startMillis = millis();
  startDate = rtc->getDateStr()+String(" ") +rtc->getTimeStr();
}
void Cooler::Stop() {
  logger->Info("Cooler stopped");
  digitalWrite(pin, LOW);
  isWorking = false;
  isManualStarted = false;
  startMillis = 0;
  startDate = "";
}
bool Cooler::IsWorking() {
  return isWorking;
}

String Cooler::toJSON(){
  if(!IsWorking()){
    return "{\"working\":\"false\"}";
  }
  return "{\"working\":\"true\", \"start_date\":\""+startDate+"\"}";
}

