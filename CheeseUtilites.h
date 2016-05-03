
String GetTimeFromStart() {
  const int secHour = 3600;
  const int secMin = 60;
  int seconds = (float) millis() / 1000.0;
  if(seconds>secHour){
    int hour = seconds/secHour;
    seconds-= hour*secMin;
    int minute = seconds/secMin;
    seconds-= minute*secMin;
    return String(hour)+"h "+String(minute)+"m "+String(seconds)+"s";
  }else if(seconds>secMin){
    int minute = seconds/secMin;
    seconds-= minute*secMin;
    return String(minute)+"m "+String(seconds)+"s";
  }
    return String(seconds)+"s";
}
