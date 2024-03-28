#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

#define PIN_TRIG_1 8
#define PIN_ECHO_1 9

#define PIN_TRIG_2 12
#define PIN_ECHO_2 11

long duration_1, cm_1;
long duration_2, cm_2;

unsigned long lastTurnTime = 0;
int turnDuration = 2000;

void setup() {
  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(PIN_TRIG_1, OUTPUT);
  pinMode(PIN_ECHO_1, INPUT);
  pinMode(PIN_TRIG_2, OUTPUT);
  pinMode(PIN_ECHO_2, INPUT);
  Serial.begin(9600); 
}

void move(bool lforward, bool rforward, int lspeed, int rspeed){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rspeed);
  analogWrite(SPEED_LEFT, lspeed);
}

void forward(int speed){
  move(false, true, speed, speed);
}

void back(int speed){
  move(true, false, speed, speed);
}

void stop(){
  move(true, false, 0, 0);
}

void turn(bool left, int speed) {
  int quarterTurnDuration = turnDuration / 4;

  if (left) {
    move(true, true, speed, speed);
    analogWrite(SPEED_RIGHT, speed);
  } else {
    move(false, false, speed, speed);
    analogWrite(SPEED_LEFT, speed);
  }

  delay(quarterTurnDuration); // Делаем четверть поворота

  while (millis() - lastTurnTime < 3 * quarterTurnDuration) {
  }
  
  stop(); 
}

void loop() {
  digitalWrite(PIN_TRIG_1, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_1, LOW);
  duration_1 = pulseIn(PIN_ECHO_1, HIGH);
  cm_1 = (duration_1 / 2) / 29.1;

  digitalWrite(PIN_TRIG_2, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_2, LOW);
  duration_2 = pulseIn(PIN_ECHO_2, HIGH);
  cm_2 = (duration_2 / 2) / 29.1;

  Serial.print("Forward: ");
  Serial.print(cm_1);
  Serial.println(" см.");
  
  Serial.print("Left: ");
  Serial.print(cm_2);
  Serial.println(" см.");

  delay(1000);

  // if (cm_1 < 10 && cm_2 < 10) { // Если оба расстояния меньше 10 см
  //   Serial.println("Расстояние меньше 10 см для обоих датчиков. Движение вперед.");
  //   forward(255); 
  // } else if (cm_1 > cm_2) { // Если расстояние от первого датчика больше, чем от второго
  //   Serial.println("Расстояние от первого датчика больше, чем от второго. Поворот налево.");
  //   turn(true, 255); 
  // } else if (cm_1 < cm_2) { // Если расстояние от второго датчика больше, чем от первого
  //   Serial.println("Расстояние от второго датчика больше, чем от первого. Поворот направо.");
  //   turn(false, 255); 
  // }
}


// void loop() {
//   digitalWrite(PIN_TRIG, LOW);
//   delayMicroseconds(5);
//   digitalWrite(PIN_TRIG, HIGH);

//   delayMicroseconds(1000);
//   digitalWrite(PIN_TRIG, LOW);

//   // Получаем время задержки для акустического сигнала на датчике (в микросекундах)
//   duration = pulseIn(PIN_ECHO, HIGH);

//   // Преобразуем время в расстояние (в сантиметрах)
//   cm = (duration / 2) / 29.1;

//   // Выводим измеренное расстояние в консоль
//   Serial.print("Расстояние до объекта: ");
//   Serial.print(cm);
//   Serial.println(" см.");

//   if(Serial.available()){
//     char input = Serial.read();
//     switch(input){
//       case 'f':
//         Serial.println("Moving forward...");
//         forward(255);
//         break;
//       case 's':
//         Serial.println("Stopping...");
//         stop();
//         break;
//       case 'b':
//         Serial.println("Moving backward...");
//         back(255);
//         break;
//       case 'a':
//         Serial.println("Turning around...");
//         turn(true, 255); 
//         break;
//       case 'l':
//         Serial.println("Turning left...");
//         turn(true, 255); 
//         break;
//       case 'r':
//         Serial.println("Turning right...");
//         turn(false, 255); 
//         break;
//     }
//   }
// }
