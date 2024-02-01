int buttonState = 0;
int buttonPreviousState = LOW;
bool buttonPressed = false;

void setup()
{
  pinMode(2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    buttonPressed = true;
  } else {
    buttonPressed = false;
  }

  if (buttonPressed) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Button pressed!");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  buttonPreviousState = buttonState;
  delay(10);
}
