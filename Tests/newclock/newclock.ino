
#include "pitches.h"
#include <LiquidCrystal.h>

#include <Keypad.h>
//const int buzzerPin = 13;
int clock1(int hr, int minute, int sec);

void beep(int note, int duration) {
  tone(buzzerPin, note, duration);
  delay(duration);
}
char w;
int date(int hr, int minute, int sec);
int rs = 19;
int en = 23;
int d4 = 18;
int d5 = 17;
int d6 = 16;
int d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int i, j, k, hr1, minute1, sec1, hr2, minute2, sec2;

int flag = 0;

// Set the LCD address to 0x27 for a 16 chars and 2 line display

const byte ROWS = 4;  //four rows

const byte COLS = 4;  //three columns

char keys[ROWS][COLS] = {

  { '1', '2', '3', '^' },

  { '4', '5', '6', 'v' },

  { '7', '8', '9', 'C' },

  { 'B', '0', 'c', 'E' }

};

byte rowPins[ROWS] = { 4, 13, 14, 27 };  //connect to the row pinouts of the keypad

byte colPins[COLS] = { 26, 25, 33, 32 };  //connect to the column pinouts of the keypad


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// long getKeypadIntegerMulti()

// {
//   long value = 0;  // the number accumulator

//   long keyvalue;  // the key pressed at current moment

//   int isnum;
//   int cnt = 0;
//   int counter = 0;

//   // Serial.println("Enter the digits ");

//   // Serial.print("You have typed: ");
//   do {
//     counter++;
//     lcd.print(" ");
//     keyvalue = keypad.getKey();  // input the key

//     isnum = (keyvalue >= '0' && keyvalue <= '9');  // is it a digit?

//     if (isnum)

//     {
//       cnt++;
//       Serial.print(keyvalue - '0');

//       lcd.print(keyvalue - '0');

//       value = value * 10 + keyvalue - '0';  // accumulate the input number
//     }
//     if (keyvalue == 'B') return -1;
//     if (keyvalue == 'E' || cnt == 2) break;

//   } while (flag == 1);  // until not a digit or while no key pressed

//   //



//   // Serial.println(" ");

//   // Serial.print("Returning from funtion: ");

//   // Serial.println(value);

//   return value;


// }  //getKeypadInteger


void setup()

{
  pinMode(buzzerPin, OUTPUT);
  pinMode(12, OUTPUT);  // led
  pinMode(2, OUTPUT);   // led
  Serial.begin(115200);
  lcd.begin(16, 2);
  digitalWrite(12, LOW);
  digitalWrite(2, LOW);
  lcd.setCursor(0, 0);

  lcd.print("WELCOME,");

  lcd.setCursor(0, 1);

  lcd.print("To Digital Clock");

  delay(2000);

  lcd.clear();

  delay(1100);
}
void alarm2() {
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
  for (int z = 0; z < 5; z++) {
    w = keypad.getKey();
    if (w == 'B') break;
    delay(100);
  }

  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
  for (int z = 0; z < 5; z++) {
    w = keypad.getKey();
    if (w == 'B') break;
    delay(100);
  }
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GS5, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);
  beep(NOTE_FS5, 250);

  for (int z = 0; z < 3; z++) {
    w = keypad.getKey();
    if (w == 'B') break;
    delay(100);
  }
  beep(NOTE_AS4, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);
  beep(NOTE_CS5, 175);
  beep(NOTE_C5, 125);
  beep(NOTE_AS4, 125);
  beep(NOTE_C5, 250);
  for (int z = 0; z < 3; z++) {
    w = keypad.getKey();
    if (w == 'B') break;
    delay(100);
  }
}
void loop() {


  if (flag == 0) {

    hr1 = sethour();

    minute1 = setmin();

    sec1 = 00;
  }


  clock1(hr1, minute1, sec1);
  delay(1000);
}
int sethour()  //for setting the hour format

{

  lcd.setCursor(0, 0);

  lcd.print("Press # To");

  lcd.setCursor(0, 1);

  lcd.print("Set HOUR:");

  int val1 = getKeypadIntegerMulti();

  Serial.println("Value is");

  Serial.println(val1);



  delay(500);



  lcd.clear();

  delay(500);

  return val1;
}


int setmin()  //for setting the minute format

{

  lcd.setCursor(0, 0);

  lcd.print("Press # To");

  lcd.setCursor(0, 1);

  lcd.print("Set MINUTE:");

  int val2 = getKeypadIntegerMulti();



  Serial.println("Value is");

  Serial.println(val2);



  delay(500);



  lcd.clear();

  delay(500);

  return val2;
}

long getKeypadIntegerMulti()

{



  long value = 0;  // the number accumulator

  long keyvalue;  // the key pressed at current moment

  int isnum;

  Serial.println("Enter the digits ");

  Serial.print("You have typed: ");



  do

  {

    keyvalue = keypad.getKey();  // input the key

    isnum = (keyvalue >= '0' && keyvalue <= '9');  // is it a digit?

    if (isnum)

    {

      Serial.print(keyvalue - '0');

      lcd.print(keyvalue - '0');

      value = value * 10 + keyvalue - '0';  // accumulate the input number
    }


  } while (isnum || !keyvalue);  // until not a digit or while no key pressed

  //



  Serial.println(" ");

  Serial.print("Returning from funtion: ");

  Serial.println(value);

  return value;


}  //getKeypadInteger

int clock1(int hr, int minute, int sec)

{



  if (hr == 0 || minute < 60 && sec == 0 || sec < 60)



  {



    // i loop for  day hour

    for (i = hr; i < 24; i++)

    {



      // j loop for day mins

      for (j = minute; j < 60; j++)

      {

        //k loop for day seconds

        for (k = sec; k < 60; k++)

        {



          lcd.print("Time: ");



          if (i <= 9) {  // for hour setting if 0  to 9 then set 0 in front of them like 01,02,03 etc.

            lcd.print("0");
          }

          lcd.print(i, DEC);

          lcd.print(":");









          if (j <= 9) {

            lcd.print("0");
          }

          lcd.print(j, DEC);

          lcd.print(":");







          if (i < 12)

          {

            if (k <= 9)

            {

              lcd.print("0");
            }



            lcd.print(k);

            lcd.print("AM");

          }



          else

          {

            if (k <= 9)

            {

              lcd.print("0");
            }



            lcd.print(k);

            lcd.print("PM");
          }
          for (int d = 0; d < 10; d++) {
            char key = keypad.getKey();

            if (key == 'A') {
              hr2 = sethour();
              Serial.print(hr2);
              Serial.println("  hr2 set");
              minute2 = setmin();
              Serial.print(minute2);
              Serial.println("  minute2 set");

              sec2 = 00;
            }
            if (i == hr2 && j == minute2) {
              lcd.clear();

              while (key != 'B') {
                lcd.setCursor(0, 0);
                lcd.print("ALARM");
                digitalWrite(12, HIGH);
                alarm2();
                key = keypad.getKey();
              }
              j++;
              digitalWrite(12, LOW);
            }
            Serial.print(i);
            Serial.print("   ");
            Serial.print(hr2);
            Serial.print("   ");
            Serial.print(j);
            Serial.print("   ");
            Serial.println(minute2);
            delay(100);
          }
          lcd.clear();
        }

        sec = 0;

        minute = 0;

        lcd.clear();
      }
    }
  }

  lcd.clear();

  hr = 0;

  minute = 0;

  sec = 0;

  flag = 1;
}