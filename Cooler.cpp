#include "Cooler.h"

Cooler::Cooler(int pin, Schedule* schedules, int length) {
  this->pin = pin;
  this->schedules = schedules;
  this->length = length;
}
void Cooler::CheckState() {

}
void Cooler::Start() {

}
void Cooler::Stop() {

}
bool Cooler::IsWorking(){
  return false;
}

