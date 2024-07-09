#include <LiquidCrystal.h>
//#include <DHT.h>
/*================================
    LCD INPUTS
  ================================*/
int rs = 19;
int en = 23;
int d4 = 18;
int d5 = 17;
int d6 = 16;
int d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/*==================================
    TIME/ALARM SETTER
  ===================================*/
int timeset = 21;
int secs, mins, hour;
int alarm1 = 22;
int hour1, min1;
int buzzpin = 13;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(buzzpin, OUTPUT);
  digitalWrite(buzzpin, LOW);
  pinMode(timeset, INPUT);
  pinMode(alarm1, INPUT);
  starter();
}

void loop() {
  // put your main code here, to run repeatedly:
  clock1();
  Serial.println(analogRead(alarm1));
  if (analogRead(alarm1) == 1023) {

    alarmset();
  }
  check();
}

void starter() {
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(0, 0);
    lcd.print("PLEASE WAIT");
    if (i % 3 == 0) {
      lcd.setCursor(0, 1);
      lcd.print("/");
      delay(100);
    } else if (i % 3 == 1) {
      lcd.setCursor(0, 1);
      lcd.print("-");
      delay(100);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("\\");
      delay(100);
    }
    lcd.clear();
  }
  lcd.print("HEYY THERE!!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("enter the time");
  delay(1500);
  lcd.clear();
  lcd.print("enter hours?");
  lcd.setCursor(0, 1);
  delay(2000);
  Serial.println(analogRead(timeset));
  hour = 12. / 1023. * analogRead(timeset);
  ;
  Serial.println(hour);
  lcd.print(hour);
  delay(1000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("enter minutes");
  lcd.setCursor(0, 1);
  delay(2000);
  Serial.println(analogRead(timeset));
  mins = 60. / 1023. * analogRead(timeset);
  Serial.println(mins);
  lcd.print(mins);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);



  lcd.print("enter seconds");
  lcd.setCursor(0, 1);
  delay(3000);
  Serial.println(analogRead(timeset));
  secs = 60. / 1023. * analogRead(timeset);
  Serial.println(secs);
  lcd.print(secs);
  lcd.clear();
  secs = secs + 3;
}
void clock1() {
  updatetime();
  lcd.setCursor(0, 0);
  lcd.print("TIME:");
  lcd.setCursor(3, 1);
  lcd.println(hour);
  lcd.setCursor(5, 1);
  lcd.print(":");
  lcd.print(mins);
  lcd.setCursor(8, 1);
  lcd.print(":");
  lcd.print(secs);
  secs = secs + 1;
  delay(1000);
  lcd.clear();
}

void alarmset() {
  lcd.print("Setting Alarm");
  delay(1000);
  lcd.clear();
  lcd.print("enter hours?");
  lcd.setCursor(0, 1);
  delay(2000);

  hour1 = 12. / 1023. * analogRead(timeset);
  ;
  Serial.println(hour1);
  lcd.print(hour1);
  delay(1000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("enter minutes");
  lcd.setCursor(0, 1);
  delay(2000);
  min1 = 60. / 1023. * analogRead(timeset);
  Serial.println(min1);
  lcd.print(min1);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  secs = secs + 7;
}

void updatetime() {
  if (secs >= 60) {
    mins = mins + 1;
    secs = secs - 60;
    ;
  }
  if (mins >= 60) {
    hour = hour + 1;
    mins = mins - 60;
  }
  if (hour >= 24) {
    hour = hour - 24;
    mins = 0;
    secs = 0;
  }
}
void check() {
  if (hour1 == hour && min1 == mins) {
    lcd.clear();
    lcd.print("ALARM");
    tone(buzzpin, 1915);
    delay(1000);  // Wait for 1000 millisecond(s)
    tone(buzzpin, 1700);
    delay(1000);  // Wait for 1000 millisecond(s)
    tone(buzzpin, 1519);
    delay(1000);
    tone(buzzpin, 1432);
    delay(1000);
    tone(buzzpin, 1275);
    delay(1000);
    tone(buzzpin, 1136);
    delay(1000);
    tone(buzzpin, 1014);
    delay(1000);
    tone(buzzpin, 0);
    delay(1000);
    secs = secs + 8;
  } else {
    noTone(buzzpin);
  }
}