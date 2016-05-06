#include "Arduino.h"
#include "Cooler.h"

Cooler::Cooler(int pin, Schedule* schedules, int length, CheeseLog* logger) {
  this->pin = pin;
  this->schedules = schedules;
  this->length = length;
  this->logger = logger;
  pinMode(this->pin, OUTPUT);

}
void Cooler::CheckState() {
  isWorking = false;
}
void Cooler::Start() {
  digitalWrite(pin, HIGH);
  isWorking = true;
}
void Cooler::Stop() {
  digitalWrite(pin, LOW);
  isWorking = false;
}
bool Cooler::IsWorking() {
  return isWorking;
}

