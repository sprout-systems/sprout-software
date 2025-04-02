#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

#define LCD_I2C_ADDRESS 0x27
//#define LCD_I2C_ADDRESS 0x3F
//SDL - 21 
//SCL - 22

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
