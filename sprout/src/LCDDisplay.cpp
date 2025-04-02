#include "../include/LCDDisplay.h"

LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 16, 2);

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

void LCD_Display(void* pvParameters) {
    SensorPointers* sensors = (SensorPointers*)pvParameters;
    
    while(1) {
        clearLCD();
        displayText("Temp: " + String(*sensors->temperature) + " C", 0, 0);
        displayText("Hum: " + String(*sensors->humidity) + "%", 1, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        clearLCD();
        displayText("pH: " + String(*sensors->phValue), 0, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
