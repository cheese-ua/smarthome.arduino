#include "Arduino.h"
#include "Cooler.h"

Cooler::Cooler(int pin, Schedule* schedules, int length, CheeseLog* logger) {
  this->pin = pin;
  this->schedules = schedules;
  this->length = length;
  this->logger = logger;
  pinMode(this->pin, OUTPUT);
  isWorking = false;
}
void Cooler::CheckState() {
  logger->Info("Check state");
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

