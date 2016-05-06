#include "CheeseLog.h"
#include "CheeseUtilites.h"
CheeseLog::CheeseLog(){
    Serial.begin(115200);
}
void CheeseLog::Info(String line) {
  String date = CheeseUtilites::GetTimeFromStart_String();
  Serial.println(date + " " + line);
}
void CheeseLog::InfoNoLine(String line) {
  Serial.print(line);
}
