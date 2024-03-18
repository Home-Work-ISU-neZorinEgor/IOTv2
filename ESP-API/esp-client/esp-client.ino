#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "iPhone (Егор)";
const char* password = "123456789";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  Serial.println("Подключение к WiFi..");
  Serial.println("Подключено к WiFi");
}

float getAverageTemperature(const String& payload) {
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);

  if (doc.containsKey("values")) {
    float sum = 0;
    int count = 0;
    for (const auto& value : doc["values"].as<JsonArray>()) {
      sum += value.as<float>();
      count++;
    }
    return sum / count;
  }
  return 0;
}

void send_post_request(float temperature) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, "http://172.20.10.10:5000/add_temperatures?value=" + String(temperature) + "&location=ru");
  int httpCode = http.POST("");

  if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
    Serial.println("POST запрос успешно отправлен");
  } else {
    Serial.print("Ошибка отправки POST запроса, код HTTP: ");
    Serial.println(httpCode);
  }

  http.end();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, "http://172.20.10.10:5000/get_temperatures?location=ru");
    int httpCode = http.GET();

    if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      float averageTemperature = getAverageTemperature(payload);
      send_post_request(averageTemperature);
    }

    http.end();
  }

  delay(5000);
}
