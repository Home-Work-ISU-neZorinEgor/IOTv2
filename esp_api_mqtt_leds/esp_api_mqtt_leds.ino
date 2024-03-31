#include <FastLED.h>

#define NUM_LEDS 15
#define PIN D5

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() {
  static uint8_t hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();
  hue += 1;
  delay(30);
}
