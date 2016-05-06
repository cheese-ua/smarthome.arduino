#include "CheeseLog.h"
#include "CheeseUtilites.h"

void CheeseLog::Info(String line) {
  String date = CheeseUtilites::GetTimeFromStart();
  Serial.println(date + " " + line);
}
void CheeseLog::InfoNoLine(String line) {
  Serial.print(line);
}
