#include <SoftwareSerial.h>

#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

unsigned long lastTurnTime = 0;
int turnDuration = 2000;

SoftwareSerial mySerial(10, 11); 

void setup() {
  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(57600);
  while (!Serial) {}
  Serial.println("Goodnight Egor!");
  mySerial.begin(9600);
  mySerial.println("Hello, Egor!");
}

void move(bool lforward, bool rforward, int lspeed, int rspeed){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rspeed);
  analogWrite(SPEED_LEFT, lspeed);
}

void forward(int l_speed, int r_speed, bool left, bool right){
  move(left, right, l_speed, r_speed);
}

void back(int speed){
  move(false, false, speed, speed);
}

void stop(){
  move(true, false, 0, 0);
}

void turn(bool left, int speed) {
  int quarterTurnDuration = turnDuration / 4;
  if (left) {
    move(false, true, speed, speed);
    analogWrite(SPEED_RIGHT, speed);
  } else {
    move(true, false, speed, speed);
    analogWrite(SPEED_LEFT, speed);
  }
  delay(quarterTurnDuration);
  while (millis() - lastTurnTime < 3 * quarterTurnDuration) {}
  stop(); 
}

void loop() {
  float coef = 1.1;
  static int leftSpeed = 100; 
  static int rightSpeed = 100; 

  static int pCount = 0; 
  static String bindSequence = ""; 
  static bool bindMode = false; 

  static bool changeSpeed = false; ////////////////////////////////////////////////////////////////
  static String readMessage = ""; 
  static int mCount = 0; 

  bool state_1l = false, state_1r = false;
  bool state_2l = false, state_2r = true;
  bool state_3l = true, state_3r = false;
  bool state_4l = true, state_4r = true;

  bool f_1l, f_1r;
  bool f_2l, f_2r;
  bool f_3l, f_3r;
  bool f_4l, f_4r;
  bool set_1 = false, set_2 = false;

  if (mySerial.available()) {
    char receivedChar = mySerial.read(); 
    Serial.write(receivedChar); 

    if (changeSpeed) {
      readMessage += receivedChar;
      mCount++;
      if (mCount >= 5) {
          readMessage = readMessage.substring(readMessage.length() - 4);
          // Вывод первых двух символов
          String firstTwo = readMessage.substring(0, 2);
          
          Serial.println();
          Serial.println();
          Serial.println(readMessage);

          // Serial.print("Первые два символа: ");
          // Serial.println(firstTwo);

          String lastTwo = readMessage.substring(readMessage.length() - 2);
          

          if (firstTwo == "B0") {
              String test_state = lastTwo;
              if (test_state == "R0"){
                  rightSpeed =  rightSpeed / coef;
              }

              if (test_state == "L0"){
                  leftSpeed = leftSpeed / coef;
              }
          }

          if (firstTwo == "F0") {
              String test_state = lastTwo;
              if (test_state == "R0"){
                  rightSpeed = rightSpeed* coef;
              }

              if (test_state == "L0"){
                  leftSpeed =  leftSpeed * coef;
              }
          }
          
          Serial.println();
          Serial.println("New speed:");
          Serial.println(leftSpeed);
          Serial.println(rightSpeed);
          // Сброс переменных и строк
          changeSpeed = false;
          readMessage = "";
          mCount = 0;
      }
  }

    if (bindMode) {
      bindSequence += receivedChar;
      pCount++;
      if (pCount >= 5) {
        bindSequence = bindSequence.substring(bindSequence.length() - 4);
        switch (bindSequence[0]) {
          case 'T': set_1 = state_1l; set_2 = state_1r; break;
          case 'S': set_1 = state_2l; set_2 = state_2r; break;
          case 'X': set_1 = state_3l; set_2 = state_3r; break;
          case 'C': set_1 = state_4l; set_2 = state_4r; break;
        }
        if ((bindSequence.substring(bindSequence.length() - 2)) == "F0") { f_1l = set_1; f_1r = set_2; }
        if ((bindSequence.substring(bindSequence.length() - 2)) == "R0") { f_2l = set_1; f_2r = set_2; }
        if ((bindSequence.substring(bindSequence.length() - 2)) == "L0") { f_3l = set_1; f_3r = set_2; }
        if ((bindSequence.substring(bindSequence.length() - 2)) == "B0") { f_4l = set_1; f_4r = set_2; }
        bindMode = false; pCount = 0; bindSequence = "";
      }
    }

    if (receivedChar == 'F') forward(leftSpeed, rightSpeed, f_1l, f_1r);
    else if (receivedChar == 'R') forward(leftSpeed, rightSpeed, f_2l, f_2r);
    else if (receivedChar == 'L') forward(leftSpeed, rightSpeed, f_3l, f_3r);
    else if (receivedChar == 'B') forward(leftSpeed, rightSpeed, f_4l, f_4r);

    if (receivedChar == 'T') forward(leftSpeed, rightSpeed, state_1l, state_1r);
    else if (receivedChar == 'S') forward(leftSpeed, rightSpeed, state_2l, state_2r);
    else if (receivedChar == 'X') forward(leftSpeed, rightSpeed, state_3l, state_3r);
    else if (receivedChar == 'C') forward(leftSpeed, rightSpeed, state_4l, state_4r);
    else if (receivedChar == '0') stop();

    else if (receivedChar == 'P') {
      bindMode = true; pCount = 0; bindSequence = "";
      Serial.println("Start bind mode");
    }

    else if (receivedChar == 'A') {
      changeSpeed = true;
      Serial.println("CHANGE SPEED");
    }
  }
  if (Serial.available()) mySerial.write(Serial.read());
}




// C - круг
// X - крестик
// S - квадрат
// T - треугольник
// Pause - режим калибровки
// Start - применить конфиг. За раз можно будет перебиндить одну кнопку 

