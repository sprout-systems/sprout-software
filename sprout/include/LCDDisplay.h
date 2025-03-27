#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LiquidCrystal.h>

//VCC -> 3.3V or 5v 
//VSS -> GND
//RS -> 18
//RW -> GND
//E -> 19
//D4 -> 25
//D5 -> 22
//D6 -> 21
//D7 -> 5 
//A -> 3.3V or 5v
//K -> GND
#define RS_PIN 18
#define E_PIN 19
#define D4_PIN 25
#define D5_PIN 22
#define D6_PIN 21
#define D7_PIN 5

extern LiquidCrystal lcd;

typedef struct {
    float* temperature;
    float* humidity;
    float* phValue;
} SensorPointers;

void initLCD();
void displayText(const String &text, uint8_t row, uint8_t col);
void clearLCD();
void LCD_Display(void *pvParameters);

#endif 
