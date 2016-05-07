#include "Arduino.h"
#include "Cooler.h"

Cooler::Cooler(int pin, DS1302* rtc, CheeseLog* logger) {
  this->pin = pin;
  this->logger = logger;
  pinMode(this->pin, OUTPUT);
  isWorking = false;
  this->rtc = rtc;

  OneTime tf1 = {11, 42};
  OneTime tt1 = {11, 43};
  Schedule s1 = {tf1, tt1};

  OneTime tf2 = {11, 50};
  OneTime tt2 = {11, 51};
  Schedule s2 = {tf2, tt2};

  length = 2;
  schedules = new Schedule[length];
  schedules[0] = s1;
  schedules[1] = s2;


}
void Cooler::CheckState() {
  bool needWork = IsNeedWorking();
  logger->Info("Cooler need work: " + String(needWork));
  if (needWork) {
    if (!isWorking)
      Start();
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

