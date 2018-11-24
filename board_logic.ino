#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SECOND 1000

const char* ssid = "G6";
const char* pass = "muiepsdpsd";

String ip;
uint8_t counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Getting started.");

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(SECOND);
  }

  auto local = WiFi.localIP();
  char* buffer = (char*)malloc(30);

  sprintf(buffer,"%d.%d.%d.%d", local[0], local[1], local[2], local[3]);
  ip = String(buffer);
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(ip);
  
  free(buffer);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "https://distance-sensor.herokuapp.com/data";
    String thumbprint = "083b717202436ecaed428693ba7edf81c4bc6230";
    String payload = String("{\"distance\":") + String(counter) + String("}");
        

    Serial.println(String("Sending at ") + url);
    Serial.println(payload);
    
    http.begin(url, thumbprint);
    http.addHeader("Content-Type", "application/json");
    http.POST(payload);
    http.end();
    
    counter++;

  }

  delay(SECOND * 5);
}
