#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void printLCD(char text[], int line, int column);
void eraseLine(int line); // line 0 or 1 of LCD Display

void setup() {
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  // testing line 1
  for (int i = 0; i < 6; i++) {
    if (i % 2 == 0)
      printLCD("Testing...", 3, 0);
    else
      eraseLine(0);
    
    delay(250);
  }

  // testing line 2
  for (int i = 0; i < 6; i++) {
    if (i % 2 == 0)
      printLCD("Testing...", 3, 1);
    else
      eraseLine(1);
    
    delay(250);
  }
}

void printLCD(char text[], int line, int column) {
  lcd.setCursor(line, column);
  lcd.print(text);
}

void eraseLine(int line) {
  lcd.setCursor(0, line);
  lcd.print("                ");
}
