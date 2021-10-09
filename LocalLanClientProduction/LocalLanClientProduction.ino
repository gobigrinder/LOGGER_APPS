#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "Airtel-Internet-01E5"
#define STAPSK  "FDD9E69A"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

HTTPClient http;
int httpCode;
String payload;

String servers[] = {
  "http://p0.local/temp",
  "http://p1.local/temp",
  "http://p2.local/temp",
  "http://p3.local/temp",
  "http://p4.local/temp",
  "http://p5.local/temp",
  "http://p6.local/temp",
  "http://p7.local/temp",
  "http://p8.local/temp",
  "http://p9.local/temp",
  "http://p10.local/temp",
  "http://p11.local/temp"
};

String get_temp(String address) {
  WiFiClient client;
  String resp = "-127.0";

  if (http.begin(client, address)) {
    httpCode = http.GET();

    if (httpCode > 0) {
      resp = http.getString();
    }
  }

  http.end();

  return resp;
}

int get_devices() {
  int n = MDNS.queryService("http", "tcp");
  return n;
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  MDNS.begin("main");

  int n = get_devices();
  while (n != 2) {
    n = get_devices();
    delay(500);
  }
}

void loop() {
  MDNS.update();

  String temps = "";
  for (int i = 0; i < 12; i++) {
    String resp = get_temp(servers[i]);
    int respLen = resp.length();
    
    temps += resp;
    temps += (i != 11) ? "," : "";
  }

  Serial.println(temps);

  delay(5000);
}
