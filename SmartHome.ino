#include <Wire.h>
#include "CheeseDHT11.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "HTTPProcessor.h"
#include "secure.h"
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include "Cooler.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

long counter = 0;
Cooler *cooler;

/***********************************************/
void setup() {
  init_secure();
  Serial.begin(115200);
  Serial.println("\nsetup: start");
  pinMode(15, OUTPUT);

  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();
  
  httpStart();
  CheeseWiFi::init();

  Schedule schedules[] = { {{10,10}, {10, 20}} };
  cooler = new Cooler(15, schedules, 1);
}


/***********************************************/
void loop() {
  httpProcess();


  if (++counter % 100 == 0) {
    Serial.print("LCD update: ");
    Serial.println(GetTimeFromStart());
    PrintDHT11ToLCD16(lcd, 0, 0);
    PrintDHT11ToLCD16(lcd, 14, 1);
    delay(500);
  } else {
    delay(50);
  }
}
