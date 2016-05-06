#ifndef COOLER
struct OneTime{
  int hour;
  int minute;
};
struct Schedule{
  OneTime from;
  OneTime to;
};

class Cooler{
  private:
    int pin;
    Schedule* schedules;
    int length;
  public:
    Cooler(int pin, Schedule* schedules, int length);
    void CheckState();
    void Start();
    void Stop();
};
#define COOLER
#endif
