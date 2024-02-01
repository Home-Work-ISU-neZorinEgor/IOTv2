const int outputPins[] = {8, 9};
const int inputPins[] = {10, 11};
int outputStates[][2] = {{LOW, HIGH}, {HIGH, LOW}};
int prevInputStatus[4] = {0};
int inputStatus[4] = {0};

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void changeInputStatus(int index) {
  for (int i = 0; i < 2; i++) {
    inputStatus[index + i] = !digitalRead(inputPins[i]);
  }

  boolean hasChanged = false;
  for (int i = 0; i < 4; i++) {
    if (memcmp(inputStatus, prevInputStatus, sizeof(inputStatus)) != 0) {
  hasChanged = true;
}

  }

  if (hasChanged && !allZeros(inputStatus, 4)) {
    memcpy(prevInputStatus, inputStatus, sizeof(prevInputStatus));
    Serial.print("Input status: ");
    for (int value : inputStatus) {
      Serial.print(value);
    }
    Serial.println();
  }
  delay(300);
}

boolean allZeros(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      return false;
    }
  }
  return true;
}

void loop() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(outputPins[0], outputStates[i][0]);
    digitalWrite(outputPins[1], outputStates[i][1]);
    changeInputStatus(i * 2);
  }
}
