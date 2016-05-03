#include <Wire.h>
#include "CheeseDHT11.h"
#include "CheeseWiFi.h"
#include "CheeseUtilites.h"
#include "secure.h"
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

long counter = 0;

void printTempOnLCD(int pin, int line) {
  ResponseDHT11 resp = CheeseDHT11::get(pin);

  if (resp.temperature < 0) {
    lcd.setCursor(0, line);
    String lineUp = "T: Err    H: Err";
    lcd.print(lineUp);
    return;
  }

  lcd.setCursor(0, line);
  String lineUp = "T: " + String(resp.temperature, DEC) + "C    H: " + String(resp.humidity, DEC) + "%";
  lcd.print(lineUp);
}

void handleJson() {
  String html = "{\"mfs\":\"" +  GetTimeFromStart()
                +  "\",\n\"temp\"=[" +  CheeseDHT11::toJSON(14, "down")
                + "," +  CheeseDHT11::toJSON(0, "up") +  "]}";
  server.send(200, "application/json", html);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
/***********************************************/
void setup() {
  init_secure();
  Serial.begin(115200);
  Serial.println("\nsetup: start");

  Wire.begin(4, 5);
  lcd.init();
  lcd.backlight();

  server.on("/json", handleJson);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  CheeseWiFi::init();
}


/***********************************************/
void loop() {
  server.handleClient();

  if (++counter % 100 == 0) {
    Serial.print("LCD update: ");
    Serial.println(GetTimeFromStart());
    printTempOnLCD(14, 1);
    printTempOnLCD(0, 0);
    delay(500);
  } else {
    delay(50);
  }
}
