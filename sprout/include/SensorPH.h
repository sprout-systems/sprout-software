#ifndef SENSOR_PH_H
#define SENSOR_PH_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define PHSensor 32 

extern float phValue;

void ReadPH_Task(void *pvParameters);

#endif
