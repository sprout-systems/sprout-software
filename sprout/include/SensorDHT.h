#ifndef SENSOR_DHT_H
#define SENSOR_DHT_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "DHT.h"
#include "MotorDriver.h"

#define DHTPIN 26   
#define DHTTYPE DHT11

extern float humidity;
extern float temperature;

void ReadDHT_Task(void *pvParameters);

#endif
