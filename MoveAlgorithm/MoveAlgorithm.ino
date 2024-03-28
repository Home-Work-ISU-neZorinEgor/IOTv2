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

  if (cm_1 < 10 && cm_2 < 10) { // Если оба расстояния меньше 10 см
    Serial.println("Расстояние меньше 10 см для обоих датчиков. Поворот направо.");
    turn(false, 255); // Поворот направо
  } else if (cm_1 < 10 && cm_2 >= 10) { // Если расстояние спереди меньше 10 см, а слева больше 10 см
    Serial.println("Расстояние спереди меньше 10 см и слева больше 10 см. Поворот налево и движение вперед.");
    turn(true, 255); // Поворот налево
    delay(500); // Небольшая задержка для поворота
  } else if (cm_2 < 10 && cm_1 >= 10) { // Если расстояние слева меньше 10 см, а спереди больше 10 см
    Serial.println("Расстояние слева меньше 10 см и спереди больше 10 см. Движение вперед.");
    forward(255); // Движение вперед
  } else if (cm_2 > 10 && cm_1 > 10) { // Если оба расстояние больше 10
    Serial.println("Оба расстояния больше 10. Поворот направа.");
    turn(true, 255); // Поворот налево
  }
}

