#include "CheeseLog.h"
#include "CheeseTime.h"
#include "CheeseUtilites.h"
CheeseLog::CheeseLog(){
    Serial.begin(115200);
}
void CheeseLog::Info(String line) {
  Serial.println(CheeseTime::Current() + String(" ") + line);
}
void CheeseLog::InfoNoLine(String line) {
  Serial.print(line);
}
