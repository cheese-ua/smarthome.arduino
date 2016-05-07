#include "Arduino.h"
#include "Cooler.h"

Cooler::Cooler(int pin, Schedule* schedules, int length, DS1302* rtc, CheeseLog* logger) {
  this->pin = pin;
  this->schedules = schedules;
  this->length = length;
  this->logger = logger;
  pinMode(this->pin, OUTPUT);
  isWorking = false;
  this->rtc = rtc;
}
void Cooler::CheckState() {
  bool needWork = IsNeedWorking();
  logger->Info("Cooler need work: " + String(needWork));
  if(needWork){
    if(!isWorking)
       Start();
  }else{
    if(isWorking)
       Stop();
  }
  logger->Info("Cooler state: " + String(isWorking));
}

String Cooler::ScheduleInfo(Schedule s) {
  return "from " + String(s.from.hour) + ":" + String(s.from.minute) + " to " + String(s.to.hour) + ":" + String(s.to.minute);
}

bool Cooler::IsNeedWorking() {
  Time t = rtc->getTime();
  logger->Info("Curr hour: "+String(t.hour)+" min: "+String(t.min));
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

void Cooler::Start() {
  logger->Info("Cooler started");
  digitalWrite(pin, HIGH);
  isWorking = true;
}
void Cooler::Stop() {
  logger->Info("Cooler stopped");
  digitalWrite(pin, LOW);
  isWorking = false;
}
bool Cooler::IsWorking() {
  return isWorking;
}

