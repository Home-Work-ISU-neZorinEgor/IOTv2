#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  static int byteCount = 0; 
  static char pm25HighByte = 0;
  static char pm25LowByte = 0;
  static char pm10HighByte = 0;
  static char pm10LowByte = 0;
  
  if (mySerial.available()){
    char c = mySerial.read();
    
    if (byteCount % 10 == 0) {
      Serial.println("======================================");
    }

    Serial.print(byteCount % 10);
    Serial.print(" Байт: ");
    Serial.println(c, HEX);
    
    if (byteCount == 2) {
      pm25LowByte = c;
    }
    
    if (byteCount == 3) {
      pm25HighByte = c;      
    }
    
    if (byteCount == 4) {
      pm10LowByte = c;
    }
    
    if (byteCount == 5) {
      pm10HighByte = c;
      
      int pm25Value = ((pm25HighByte * 256) + pm25LowByte) / 10;
      Serial.print("PM2.5 value (μg /m ): ");
      Serial.println(pm25Value);
      
      int pm10Value = ((pm10HighByte * 256) + pm10LowByte) / 10;
      Serial.print("PM10 value (μg /m ): ");
      Serial.println(pm10Value);
      
      pm25LowByte = 0;
      pm25HighByte = 0;
      pm10LowByte = 0;
      pm10HighByte = 0;
    }
    
    byteCount++; 
    
    if (byteCount == 10) {
      byteCount = 0; 
    }
  }
}
