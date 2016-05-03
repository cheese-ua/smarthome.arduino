#include <Wire.h>
#include "dht11.h"
#include "wifi.h"
#include "secure.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPhoto = A0;
long counter = 0;
int leds[] = {12, 13, 15};


void printTemp(int pin, String name, WiFiClient client) {
  ResponseDHT11 resp = MyDHT11::getTemp(pin);

  if (resp.temperature<0) {
    client.print("{\"pin\":");
    client.print(pin);
    client.print(",\"name\":\"");
    client.print(name);
    client.print("\",\"error\":\"Read failed\"}");
    return;
  }

  client.print("{\"pin\":");
  client.print(pin);
  client.print(",\"name\":\"");
  client.print(name);
  client.print("\",\"t\":");
  client.print(resp.temperature);
  client.print(",\"h\":");
  client.print(resp.humidity);
  client.print("}");
}

void printTempOnLCD(int pin, int line) {
  ResponseDHT11 resp = MyDHT11::getTemp(pin);

  if (resp.temperature<0) {
    lcd.setCursor(0, line);
    String lineUp = "T: Err    H: Err";
    lcd.print(lineUp);
    return;
  }

  lcd.setCursor(0, line);
  String lineUp = "T: " + String(resp.temperature, DEC) + "C    H: " + String(resp.humidity, DEC) + "%";
  lcd.print(lineUp);
}

void printPhoto(WiFiClient client) {
  client.print("{\"pin\":");
  client.print(pinPhoto);
  client.print(",\"val\":");
  int raw = analogRead( pinPhoto );
  client.print(raw);
  client.print("}");
}

/***********************************************/
void setup() {
  init_secure();
  Serial.begin(115200);
  Serial.println("\nsetup: start");

  Wire.begin(4, 5);
  lcd.init();           
  lcd.init();
  lcd.backlight();

  MyWiFi::init_wifi();

  pinMode( pinPhoto, INPUT);
  for (int i = 0; i < 3; i++) {
    pinMode( leds[i], OUTPUT);
    digitalWrite( leds[i], LOW);
  }
}

void ledOn(int pin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite( leds[i], LOW);
    Serial.printf("Led %d off\n", leds[i]);
  }
  Serial.printf("Led %d on\n", leds[pin]);
  digitalWrite( leds[pin], HIGH);
}

String GetTimeFromStart() {
  float minutes = (float) millis() / 1000.0 ;
  return "";
}

/***********************************************/
void loop() {
  if(++counter % 100 == 0){
    Serial.println("LCD start");
    printTempOnLCD(14,1);
    printTempOnLCD(0, 0);
    delay(500);
  }else{
    delay(50);
  }
  WiFiClient client = MyWiFi::server.available();
  if (!client) {
    return;
  }
  Serial.print("Loop ");
  Serial.println(millis());

  while (!client.available()) {
    delay(1);
  }
  ledOn(++counter % 3);
  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
  client.print(html);

  client.print("{\"mfs\":\"");
  client.print(GetTimeFromStart());
  client.print("\",\"temp\"=[");
  printTemp(14, "s", client);
  client.print("],\"photo\"=");
  printPhoto(client);
  client.print("}");
  client.flush();
  client.stop();
}
