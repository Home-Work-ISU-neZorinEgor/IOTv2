#define mot1 11
#define mot2 10

void setup() {
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  analogWrite(mot1, 0);
  analogWrite(mot2, 0);
  
  Serial.begin(9600);
  Serial.println("H-bridge motor control");
  Serial.println("Commands: ");
  Serial.println("1. left <speed>, right <speed> - to change direction and set speed (0-255)");
  Serial.println("2. stop - to stop");
}

void motorControl(const char* direction, int speed) {
  if (strcmp(direction, "right") == 0) {
    analogWrite(mot1, speed);
    analogWrite(mot2, 0);
  } else if (strcmp(direction, "left") == 0) {
    analogWrite(mot1, 0);
    analogWrite(mot2, speed);
  } else if (strcmp(direction, "stop") == 0) {
    analogWrite(mot1, 0);
    analogWrite(mot2, 0);
  } else {
    Serial.println("Error!!! Invalid direction");
    return;
  }
  
  Serial.print(">>> Direction: ");
  Serial.print(direction);
  Serial.print(", speed: ");
  Serial.println(speed);
}

void loop() {
  if (Serial.available() > 0) {
    char input[20];
    int index = 0;
    while (Serial.available() > 0) {
      char character = Serial.read();
      if (character == '\n') {
        break;
      }
      input[index++] = character;
      delay(2);
    }
    input[index] = '\0';
    
    char* direction = strtok(input, " ");
    char* speedStr = strtok(NULL, " ");
    
    if (strcmp(direction, "stop") == 0) {
      motorControl(direction, 0); // Call motorControl with speed 0 for "stop"
      delay(2000);
    } else {
      if (speedStr == NULL) {
        Serial.println("Error!!! Speed not provided");
        return;
      }
      
      int speed = atoi(speedStr);
      if (speed < 0 || speed > 255) {
        Serial.println("Error!!! Speed out of range (0-255)");
        return;
      }
      
      motorControl(direction, speed);
      delay(2000);
    }
  }
}
