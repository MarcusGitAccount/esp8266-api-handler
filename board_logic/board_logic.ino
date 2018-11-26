#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SECOND 1000
#define TRIG 5 // D1
#define ECHO 4 // D2

const char* ssid = "G6";
const char* pass = "muiepsdpsd";

String ip;

float read_distance() {
  unsigned long start_time, end_time, total_time;
  
  // 10us trig signal up to start measurement
  digitalWrite(TRIG, LOW);
  delay(10);
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  
  // determine how long echo is high
  // do nothing while echo is 0
  //  while (digitalRead(ECHO) == LOW) {
  //    start_time = millis();
  //  }
  //  while (digitalRead(ECHO) == HIGH) {
  //    end_time = millis();
  //  }
  //  
  total_time = pulseIn(ECHO, HIGH);

  Serial.printf("%d %d %.2f\n", start_time, end_time, (end_time - start_time) / 2.0 * 0.0343);

  return total_time / 2.0 * 0.0343;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Getting started.");
  Serial.println("Attempting to connect to wifi");

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

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    float distance = read_distance();
    String url = "https://distance-sensor.herokuapp.com/data";
    String thumbprint = "083b717202436ecaed428693ba7edf81c4bc6230";
    String payload = String("{\"distance\":") + String(distance) + String("}");
        

    Serial.print("Acquired the following distance: ");
    Serial.println(distance);
    Serial.println(String("Sending at ") + url);
    Serial.println(payload);
    
    http.begin(url, thumbprint);
    http.addHeader("Content-Type", "application/json");
    http.POST(payload);
    http.end();
  }

  delay(SECOND * 2);
}
