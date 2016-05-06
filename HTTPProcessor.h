#include "CheeseDHT11.h"
ESP8266WebServer httpServer(80);
bool isOn=false;

void httpProcess(){
    httpServer.handleClient();
}
void handleJson() {
  String message = "{\"mfs\":\"" +  GetTimeFromStart()
                +  "\",\n\"temp\"=[" +  CheeseDHT11::toJSON(14, "down")
                + "," +  CheeseDHT11::toJSON(0, "up") +  "]}";
  httpServer.send(200, "application/json", message);
  Serial.println("handleJson: "+message);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += httpServer.uri();
  message += "\nMethod: ";
  message += (httpServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += httpServer.args();
  message += "\n";
  for (uint8_t i = 0; i < httpServer.args(); i++) {
    message += " " + httpServer.argName(i) + ": " + httpServer.arg(i) + "\n";
  }
  httpServer.send(404, "text/plain", message);
  Serial.println("handleNotFound: "+message);
}

String createRowDHT11(int pin){
  ResponseDHT11 resp = CheeseDHT11::get(pin);
  return "<tr><td>"+String(pin)+"</td><td>"+String(resp.temperature)+"</td><td>"+String(resp.humidity)+"</td></tr>";
}

void handleAdmin(){
  String html="<html></body><table><tr><td>PIN</td><td>Temperature</td><td>Humidity</td></tr>"
  +createRowDHT11(0)+createRowDHT11(14)+"</table></body></html>";
  httpServer.send(200, "text/html", html);
  Serial.println("handleAdmin: "+html);
}

void handle220(){
  isOn=!isOn;
  String html="<html></body><b>SWITCH: "
  +String(isOn?"<font color='red'>ON</font>":"<font color='green'>OFF</font>")+"</b></body></html>";
  httpServer.send(200, "text/html", html);
  Serial.println("handleAdmin: "+html);
  digitalWrite(15, isOn?HIGH:LOW);  
}
void httpStart(){
  httpServer.on("/json", handleJson);
  httpServer.on("/admin", handleAdmin);
  httpServer.on("/220", handle220);
  httpServer.onNotFound(handleNotFound);

  httpServer.begin();
  Serial.println("HTTP server started");
}


