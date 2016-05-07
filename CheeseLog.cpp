#include "CheeseLog.h"
#include "CheeseUtilites.h"
CheeseLog::CheeseLog(DS1302* rtc){
    Serial.begin(115200);
    this->rtc = rtc;
}
void CheeseLog::Info(String line) {
  Serial.println(rtc->getDateStr()+String(" ") +rtc->getTimeStr() + String(" ") + line);
}
void CheeseLog::InfoNoLine(String line) {
  Serial.print(line);
}
