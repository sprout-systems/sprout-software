#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define ENA   12
#define IN1   13
#define IN2   14
#define ENB   27
#define IN3   33
#define IN4   15

typedef struct {
    float* desiredTemperature;
    float* currentTemperature;
} temperaturePointers;

void initializeMotorDriver();
void peltierCooling();
void peltierHeating();
void peltierOff();
void fanOn();
void temperatureControl(void *pvParameters);

#endif 
