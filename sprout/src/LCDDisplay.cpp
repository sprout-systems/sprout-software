#include "../include/LcdDisplay.h"

LiquidCrystal lcd(RS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

void initLCD() {
  lcd.begin(16, 2);  
  lcd.clear();
}

void displayText(const String &text, uint8_t row, uint8_t col) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void clearLCD() {
  lcd.clear();
}

void LCD_Display(float temp, float hum, float ph) {
  clearLCD();
  displayText("Temp: " + String(temp) + " C", 0, 0);
  displayText("Hum: " + String(hum) + "%", 1, 0);
  vTaskDelay(pdMS_TO_TICKS(2000));

  clearLCD();
  displayText("pH: " + String(ph), 0, 0);
  vTaskDelay(pdMS_TO_TICKS(2000));
}
