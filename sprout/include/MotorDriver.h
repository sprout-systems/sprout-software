#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "SensorDHT.h"

#define IN1   13
#define IN2   14
#define IN3   33
#define IN4   15
#define IN5   16
#define IN6   33
#define IN7   4 
#define IN8   13

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
void pumpOn();
void pumpOff();
void pumpWater();
void LedOn();
void LedOff();

#endif 
