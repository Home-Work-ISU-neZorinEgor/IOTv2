int d = 75;
int d1 = 100;
int layerPins[] = {A0, A1};
int columnPins[] = {2, 3, 4, 5};
int numLayers = sizeof(layerPins) / sizeof(layerPins[0]);

void setup() {
  for (int i = 0; i < numLayers; i++) {
    pinMode(layerPins[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(columnPins) / sizeof(columnPins[0]); i++) {
    pinMode(columnPins[i], OUTPUT);
  }
}

void displayAllCombinations(int numLayers, int delayTime) {
  for (int layer = 0; layer < numLayers; layer++) {
    for (int col1 = 0; col1 < 1; col1++) {
      for (int col2 = 0; col2 < 4; col2++) {
        for (int i = 0; i < numLayers; i++) {
          digitalWrite(layerPins[i], layer == i ? HIGH : LOW);
        }
        digitalWrite(columnPins[0], col1 == 0 ? HIGH : LOW);
        digitalWrite(columnPins[1], col1 == 1 ? HIGH : LOW);
        digitalWrite(columnPins[2], col1 == 2 ? HIGH : LOW);
        digitalWrite(columnPins[3], col1 == 3 ? HIGH : LOW);
        digitalWrite(columnPins[0], col2 == 0 ? HIGH : LOW);
        digitalWrite(columnPins[1], col2 == 1 ? HIGH : LOW);
        digitalWrite(columnPins[2], col2 == 2 ? HIGH : LOW);
        digitalWrite(columnPins[3], col2 == 3 ? HIGH : LOW);
        delay(delayTime);
      }
    }
  }
}

void loop() {
  displayAllCombinations(numLayers, 500); // Отображаем все комбинации с задержкой 500 миллисекунд
}
