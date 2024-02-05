const int NUM_OUTPUT_PINS = 2;
const int NUM_INPUT_PINS = 2;
const int DELAY_TIME = 300;

const int outputPins[NUM_OUTPUT_PINS] = {8, 9};
const int inputPins[NUM_INPUT_PINS] = {10, 11};
const int outputStates[][NUM_OUTPUT_PINS] = {{LOW, HIGH}, {HIGH, LOW}};
int prevInputStatus[NUM_INPUT_PINS * NUM_OUTPUT_PINS] = {0};
int inputStatus[NUM_INPUT_PINS * NUM_OUTPUT_PINS] = {0};

// Инициализация пинов в режиме ввода/вывода
void initializePins() {
  for (int i = 0; i < NUM_OUTPUT_PINS; i++) {
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}

// Вывод текущего состояния входов в Serial Monitor
void printInputStatus() {
  Serial.print("Input status: ");
  for (int& value : inputStatus) {
    Serial.print(value);
  }
  Serial.println();
}

// Обновление состояния входов
void updateInputStatus(int index) {
  for (int i = 0; i < NUM_INPUT_PINS; i++) {
    inputStatus[(index * NUM_INPUT_PINS) + i] = !digitalRead(inputPins[i]);
  }
}

// Проверка, изменилось ли состояние входов
bool hasInputChanged() {
  return memcmp(inputStatus, prevInputStatus, sizeof(inputStatus)) != 0;
}

// Проверка, все ли элементы массива равны нулю
bool allZeros(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      return false;
    }
  }
  return true;
}

// Обновление состояния выходов
void updateOutputPins(int index) {
  for (int i = 0; i < NUM_OUTPUT_PINS; i++) {
    digitalWrite(outputPins[i], outputStates[index][i]);
  }
}

void setup() {
  // Инициализация пинов и Serial
  initializePins();
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < NUM_OUTPUT_PINS; i++) {
    // Установка состояния выходов
    updateOutputPins(i);

    // Обновление состояния входов и проверка изменений
    updateInputStatus(i);

    // Если состояние входов изменилось и не все значения нулевые, вывод в Serial
    if (hasInputChanged() && !allZeros(inputStatus, NUM_INPUT_PINS * NUM_OUTPUT_PINS)) {
      memcpy(prevInputStatus, inputStatus, sizeof(prevInputStatus));
      printInputStatus();
    }
    
    delay(DELAY_TIME);
  }
}
