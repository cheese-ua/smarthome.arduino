#include "CheeseDHT.h"
#include "Cooler.h"
ESP8266WebServer httpServer(80);
bool isOn = false;
Cooler* httpCooler;
DS1302* httpRTC;
String httStartTime = "";
CheeseDHT *httpdhtUp;
CheeseDHT *httpdhtDown;


// use https://kangax.github.io/html-minifier/ to minify
const String htmlTemplate = "<style>table{font-size:20;border:1px solid #a9a9a9;background-color:#BCE0FF;opacity:.9;line-height:20px;padding:2px;width:500px}thead{background-color:#4C86E2;border:1px solid #000;font-weight:700;padding:3px}a{font-weight:700;background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#6D9FE7),color-stop(100%,#6D9FE7));-webkit-border-radius:3px;-moz-border-radius:3px;border-radius:3px;padding:5px 11px;-moz-box-shadow:0 2px 2px #0E4088;-webkit-box-shadow:0 2px 2px #0E4088;box-shadow:0 2px 2px #0E4088}</style><script>function SetCoolerState(t){if(confirm(\"Set cooler state: \"+t+\"?\")){alert(\"Start set state: \"+t);var e=new XMLHttpRequest;e.open(\"GET\",\"/set_cooler_state/\"+t,!0),e.send()}}function SetLigthState(t){if(confirm(\"Start set light state: \"+t+\"?\")){alert(\"Set state: \"+t);var e=new XMLHttpRequest;e.open(\"GET\",\"/set_cooler_state/\"+t,!0),e.send()}}function pad_left(t,e,o){for(;(t+\"\").length<e;)t=o+t;return t}function refresh(){location.reload()}</script><body style=background-color:#E8F8FF><center><br><table><thead><tr><td>Name<td>Value</thead><tr><td>Version<td>#app_version#<tr><td>Start time<td>#start_date#<tr><td>Page refresh<td><p id=page_date><tr><td>ESP date<td>#esp_date#<tr><td>Cooler state<td>#curr_cooler_state#</table><br><table><thead><tr><td>Name<td style=width:100px>Temperature<td style=width:100px>Humidity</thead>#rows_dht11#</table><br><br><br><a href='javascript:SetCoolerState(\"#set_cooler_state#\");'>Set cooler state: #set_cooler_state#</a><script>var pd=new Date;document.getElementById(\"page_date\").innerHTML=pad_left(pd.getDate(),2,\"0\")+\".\"+pad_left(pd.getMonth()+1,2,\"0\")+\".\"+pd.getFullYear()+\" \"+pad_left(pd.getHours(),2,\"0\")+\":\"+pad_left(pd.getMinutes(),2,\"0\")+\":\"+pad_left(pd.getSeconds(),2,\"0\"),setTimeout(refresh,3e4)</script></center>";

void httpProcess(CheeseDHT *_dhtUp, CheeseDHT *_dhtDown) {
  httpdhtUp = _dhtUp;
  httpdhtDown = _dhtDown;
  httpServer.handleClient();
}
void handleJson() {
  String message = "{\"start_date\":\"" +  httStartTime
                   +  "\",\"curr_date\":\"" +  httpRTC->getDateStr() + " " + httpRTC->getTimeStr()
                   +  "\",\n\"temp\"=[" +  httpdhtDown->toJSON()
                   + "," +  httpdhtUp->toJSON() +  "], \"cooler\":" + httpCooler->toJSON() + "}";
  httpServer.send(200, "application/json", message);
  Serial.println("handleJson: " + message);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += " URI: ";
  message += httpServer.uri();
  message += "\n Method: ";
  message += (httpServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n Arguments: ";
  message += httpServer.args();
  message += "\n";
  for (uint8_t i = 0; i < httpServer.args(); i++) {
    message += " " + httpServer.argName(i) + ": " + httpServer.arg(i) + "\n";
  }
  httpServer.send(404, "text/plain", message);
  Serial.println("handleNotFound: " + message);
}

String createRowDHT(CheeseDHT* dht) {
  ResponseDHT resp = dht->get();
  return "<tr><td>" + String(dht->pin) + "</td><td>" + String(resp.temperature) + "</td><td>" + String(resp.humidity) + "</td></tr>";
}

void handleAdmin() {
  String html = htmlTemplate;
  bool isCoolerWork = httpCooler->IsWorking();
  html.replace("#curr_cooler_state#", isCoolerWork ? "Working" : "Stopped");
  html.replace("#set_cooler_state#", isCoolerWork ? "off" : "on");
  html.replace("#rows_dht11#", createRowDHT(httpdhtUp) + createRowDHT(httpdhtDown));
  html.replace("#start_date#", CheeseUtilites::GetTimeFromStart_String());
  html.replace("#app_version#", "1.0.1.1");
  html.replace("#esp_date#", httpRTC->getDateStr() + String(" ") + httpRTC->getTimeStr());

  httpServer.send(200, "text/html", html);
  Serial.println("handleAdmin: " + html);
}

void set_cooler_state_on() {
  httpCooler->Start(true);
}

void set_cooler_state_off() {
  httpCooler->Stop();
}

void httpStart(Cooler* cooler, DS1302* rtc) {
  httpRTC = rtc;
  httpCooler = cooler;
  httStartTime = rtc->getDateStr() + String(" ") + rtc->getTimeStr();
  httpServer.on("/json", handleJson);
  httpServer.on("/admin", handleAdmin);
  httpServer.on("/", handleJson);
  httpServer.on("/set_cooler_state/on", set_cooler_state_on);
  httpServer.on("/set_cooler_state/off", set_cooler_state_off);
  httpServer.onNotFound(handleNotFound);

  httpServer.begin();
  Serial.println("HTTP server started");
}


