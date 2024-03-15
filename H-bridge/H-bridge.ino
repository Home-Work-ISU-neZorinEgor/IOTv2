#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* apSSID = "ESP8266_AP"; 
const char* apPassword = "12345678"; 

void setup() {
  Serial.begin(115200);

  // Настройка ESP8266 в режиме точки доступа
  WiFi.softAP(apSSID, apPassword);

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(apIP);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Отправляем GET запрос на указанный URL
    WiFiClient client;
    http.begin(client, "http://192.168.4.2:5000/temperature/all?location=home");
    int httpCode = http.GET();
    
    // Если ответ получен успешно
    if (httpCode > 0) {
      // Читаем ответ и выводим в Serial Monitor
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(http.errorToString(httpCode).c_str());
    }
    
    http.end();
  }
  
  delay(5000); 
}
