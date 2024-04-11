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

void move(bool l, bool r, int lspeed, int rspeed){
  digitalWrite(DIR_RIGHT, r);
  digitalWrite(DIR_LEFT, l);
  analogWrite(SPEED_RIGHT, rspeed);
  analogWrite(SPEED_LEFT, lspeed);
}

void forward(int s, bool l, bool r){
  move(l, r, s, s);
}

void back(int s){
  move(false, false, s, s);
}

void stop(){
  move(true, false, 0, 0);
}

void turn(bool l, int s) {
  int q = turnDuration / 4;
  if (l) {
    move(false, true, s, s);
    analogWrite(SPEED_RIGHT, s);
  } else {
    move(true, false, s, s);
    analogWrite(SPEED_LEFT, s);
  }
  delay(q);
  while (millis() - lastTurnTime < 3 * q) {}
  stop(); 
}

void loop() {
  static int p = 0; 
  static String bs = ""; 
  static bool bm = false; 
  bool s1l = false, s1r = false;
  bool s2l = false, s2r = true;
  bool s3l = true, s3r = false;
  bool s4l = true, s4r = true;

  bool f1l, f1r;
  bool f2l, f2r;
  bool f3l, f3r;
  bool f4l, f4r;
  bool set1 = false, set2 = false;

  if (mySerial.available()) {
    char rc = mySerial.read(); 
    Serial.write(rc); 

    if (bm) {
      bs += rc;
      p++;
      if (p >= 5) {
        bs = bs.substring(bs.length() - 4);
        switch (bs[0]) {
          case 'T': set1 = s1l; set2 = s1r; break;
          case 'S': set1 = s2l; set2 = s2r; break;
          case 'X': set1 = s3l; set2 = s3r; break;
          case 'C': set1 = s4l; set2 = s4r; break;
        }
        if ((bs.substring(bs.length() - 2)) == "F0") { f1l = set1; f1r = set2; }
        if ((bs.substring(bs.length() - 2)) == "R0") { f2l = set1; f2r = set2; }
        if ((bs.substring(bs.length() - 2)) == "L0") { f3l = set1; f3r = set2; }
        if ((bs.substring(bs.length() - 2)) == "B0") { f4l = set1; f4r = set2; }
        bm = false; p = 0; bs = "";
      }
    }
    if (rc == 'F') forward(255, f1l, f1r);
    else if (rc == 'R') forward(255, f2l, f2r);
    else if (rc == 'L') forward(255, f3l, f3r);
    else if (rc == 'B') forward(255, f4l, f4r);
    if (rc == 'T') forward(255, s1l, s1r);
    else if (rc == 'S') forward(255, s2l, s2r);
    else if (rc == 'X') forward(255, s3l, s3r);
    else if (rc == 'C') forward(255, s4l, s4r);
    else if (rc == '0') stop();
    else if (rc == 'P') {
      bm = true; p = 0; bs = "";
      Serial.println("Start bind mode");
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

