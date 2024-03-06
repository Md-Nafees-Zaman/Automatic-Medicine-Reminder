// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("circuitschools.");
}

void loop() {

  lcd.print("Arduino");  // Prints "Arduino" on the LCD
  delay(3000);           // 3 seconds delay
  lcd.setCursor(2, 1);   // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("LCD Tutorial");
  delay(3000);
  lcd.clear();  // Clears the display
  lcd.blink();  //Displays the blinking LCD cursor
  delay(4000);
  lcd.setCursor(7, 1);
  delay(3000);
  lcd.noBlink();  // Turns off the blinking LCD cursor
  lcd.cursor();   // Displays an underscore (line) at the position to which the next character will be written
  delay(4000);
  lcd.noCursor();  // Hides the LCD cursor
  lcd.clear();     // Clears the LCD screen
}