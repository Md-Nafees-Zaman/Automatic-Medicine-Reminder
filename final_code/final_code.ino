#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <Keypad.h>
//#include <ESP32Servo.h>

//Servo myservo1, myservo2;
int a = 2, b = 5, c = 12, alarm_state = 0, mn2 = -1;

RTC_DS3231 rtc;

char daysOfWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

int flag = 1;
int pos = 0;
int Lcount = -32760;
//int buzz = 13;
//int addr = 17;
struct alarms {
  int set = 0;
  int hour = -1;
  int minute = -1;
};

alarms arm[5];
const char* ssid = "Zaman";
const char* password = "blacksheep";

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 21600;
const int daylightOffset_sec = 3600;
int rs = 19;
int en = 23;
int d4 = 18;
int d5 = 17;
int d6 = 16;
int d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

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

int hr, mn;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void timeScreen() {          // function to display Date and time in LCD screen
  DateTime now = rtc.now();  // take rtc time and print in display
  hr = now.hour();
  mn = now.minute();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  //delay(100);
}
void printLocalTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.print("Connecting to %s ", ssid);
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print("WiFi");
  WiFi.begin(ssid, password);
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    //timeScreen();
    delay(200);
    lcd.print(".");
    cnt++;
    if (cnt > 40) break;
  }
  if (cnt < 40) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" CONNECTED");
    delay(1000);
  }
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  lcd.clear();
  lcd.setCursor(0, 0);
  int s = timeinfo.tm_sec;
  //h -= 22;
  int m = timeinfo.tm_min;
  int h = timeinfo.tm_hour;
  int M = timeinfo.tm_mon;
  M++;
  int d = timeinfo.tm_mday;
  int y = timeinfo.tm_year;
  y -= 100;
  // Serial.print(h);
  // Serial.print(" : ");
  // Serial.print(m);
  // Serial.print(" : ");
  // Serial.print(s);
  // Serial.print(" : ");
  // Serial.print(d);
  // Serial.print(" : ");
  // Serial.print(M);
  // Serial.print(" : ");
  // Serial.print(y);
  // Serial.println(" : ");
  rtc.adjust(DateTime(y, M, d, h, m, s));
  // lcd.print(s, DEC);
  // lcd.print(":");
  // lcd.print(m, DEC);
  // lcd.print(":");
  // lcd.print(h, DEC);
  // //lcd.println(&timeinfo, %B %d %Y");
  // lcd.setCursor(0, 1);
  //lcd.println(&timeinfo, %a %H:%Y:%S");
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval* t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() {
  Serial.begin(115200);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);


  if (!rtc.begin()) {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1)
      ;
  }
  //rtc.adjust(DateTime(2024, 2, 24, 21, 30, 0)); // adjust time manually
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  // set notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);

  /**
   * NTP server address could be aquired via DHCP,
   *
   * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
   * otherwise SNTP option 42 would be rejected by default.
   * NOTE: configTime() function call if made AFTER DHCP-client run
   * will OVERRIDE aquired NTP server address
   */
  sntp_servermode_dhcp(1);  // (optional)

  /**
   * This will set configured ntp servers and constant TimeZone/daylightOffset
   * should be OK if your time zone does not need to adjust daylightOffset twice a year,
   * in such a case time adjustment won't be handled automagicaly.
   */
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  /**
   * A more convenient approach to handle TimeZones with daylightOffset 
   * would be to specify a environmnet variable with TimeZone definition including daylight adjustmnet rules.
   * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
   */
  //configTzTime(time_zone, ntpServer1, ntpServer2);

  //connect to WiFi
}


int sethour()  //for setting the hour format

{
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Press 'D' To");

  lcd.setCursor(0, 1);

  lcd.print("Set HOUR:");

  int val1 = getKeypadIntegerMulti();

  Serial.println("Value is");

  Serial.println(val1);

  delay(500);

  lcd.clear();

  return val1;
}


int setmin()  //for setting the minute format

{
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Press 'D' To");

  lcd.setCursor(0, 1);

  lcd.print("Set MINUTE:");

  int val2 = getKeypadIntegerMulti();

  Serial.println("Value is");

  Serial.println(val2);

  delay(500);
  lcd.clear();
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

  Serial.println(" ");
  Serial.print("Returning from funtion: ");
  Serial.println(value);

  return value;
}  //getKeypadInteger

void set_alarm() {
  if (arm[pos].set == 1) {
    lcd.clear();
    arm[pos].set = 0;
    lcd.print("Alarm");
    lcd.print(pos + 1);
    lcd.print(" Deleted!");
    delay(1000);
  } else {
    arm[pos].set = 1;
    arm[pos].hour = sethour();
    // Serial.print(hr2);
    //Serial.println("  hr2 set");
    arm[pos].minute = setmin();
  }
  menu1();
}

void m1() {
  while (flag == 1) {

    char key = keypad.getKey();

    if (key == '^' && pos > 0) {
      pos--;
      menu1();
    } else if (key == 'v' && pos < 3) {
      pos++;
      menu1();
    } else if (key == 'B') break;
    else if (key == 'E') set_alarm();
  }
}

void menu1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (pos == 0) {

    if (arm[0].set) {
      lcd.print("Del Alarm1 ");
      lcd.print(arm[0].hour);
      lcd.print(":");
      lcd.print(arm[0].minute);
    } else {
      lcd.print("Set Alarm1 ");
      lcd.print("hh:mm");
    }
    lcd.setCursor(4, 1);
    lcd.print("Alarm2 ");
    if (arm[1].set) {
      lcd.print(arm[1].hour);
      lcd.print(":");
      lcd.print(arm[1].minute);
    } else {
      lcd.print("hh:mm");
    }
  } else {
    lcd.print("    Alarm");
    lcd.print(pos);
    lcd.print(" ");
    if (arm[pos - 1].set) {
      lcd.print(arm[pos - 1].hour);
      lcd.print(":");
      lcd.print(arm[pos - 1].minute);
    } else lcd.print("hh:mm");
    lcd.setCursor(0, 1);

    if (arm[pos].set) {
      lcd.print("Del Alarm");
      lcd.print(pos + 1);
      lcd.print(" ");
      lcd.print(arm[pos].hour);
      lcd.print(":");
      lcd.print(arm[pos].minute);
    } else {
      lcd.print("Set Alarm");
      lcd.print(pos + 1);
      lcd.print(" ");
      lcd.print("hh:mm");
    }
  }
}

void selector(int s) {
  if (s == 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  } else if (s == 1) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
  } else if (s == 2) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
  } else if (s == 3) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
  } else if (s == 4) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  } else if (s == 5) {
    // digitalWrite(a, HIGH);
    // digitalWrite(b, LOW);

    // myservo1.write(90);
    //digitalWrite(c, LOW);
  } else if (s == 6) {
    //digitalWrite(a, LOW);
    //digitalWrite(b, HIGH);
    // digitalWrite(c, HIGH);


    //myservo2.write(90);
  } else if (s == 7) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
  }
}


void check_alarm() {
  for (int i = 0; i < 4; i++) {
    if (arm[i].set == 1 && arm[i].hour == hr && arm[i].minute == mn) {

      lcd.clear();
      lcd.print("Take Medicine");

      lcd.setCursor(0, 1);
      lcd.print("from box ");
      lcd.print(i + 1);
      mn2 = mn;  // mn2 temporarily save the current minute that has alarm.


      while (flag) {
        if (Lcount == 0)  // loop count value is set to minimize at each iterartion
        {
          if (pos == 3) Lcount = 250;  // longer loop value for 4th alarm
          else Lcount = 200;           // general loop value for alarms.
          selector(i + 1);             // selects output combination
        }

        else if (pos == 0 && Lcount == 100)  // first alarm sequence
        {
          selector(7);
        } else if (pos == 1)  // 2nd alarm sequence
        {
          if (Lcount == 100) selector(7);
          else if (Lcount == 55) selector(0);
          else if (Lcount == 45) selector(7);

        } else if (pos == 2)  // 3rd alarm sequence
        {
          if (Lcount == 110) selector(7);
          else if (Lcount == 80) selector(0);
          else if (Lcount == 70) selector(7);
          else if (Lcount == 40) selector(0);
          else if (Lcount == 30) selector(7);

        } else if (pos == 3)  // 4th alarm sequence
        {
          if (Lcount == 190) selector(7);
          else if (Lcount == 150) selector(0);
          else if (Lcount == 140) selector(7);
          else if (Lcount == 100) selector(0);
          else if (Lcount == 90) selector(7);
          else if (Lcount == 50) selector(0);
          else if (Lcount == 40) selector(7);
        }
        char key = keypad.getKey();
        if (key) {
          return;
        }
        delay(15);
        Lcount--;
      }
    }
  }
}

int L = 0;
void loop() {
  if (L == 0) L = 15;
  if (L == 15) {
    Lcount = 0;
    selector(0);
    timeScreen();
    if (mn2 != mn) check_alarm();  // when temporary minute is not equal to current minute
    if (mn2 != mn) mn2 = -1;       // while changing the temporary minute so that
  }
  char key = keypad.getKey();
  if (key == 'C') {
    printLocalTime();
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Connecting to Wifi");
    // delay(1000);

  } else if (key) {
    pos = 0;
    menu1();
    m1();
  }
  delay(50);
  L--;
}
