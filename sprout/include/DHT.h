#ifndef DHTTASK_H
#define DHTTASK_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <DHT.h>

#define DHTPIN PA3
#define DHTTYPE DHT11

void DHT_Task(void *pvParameters);  

#endif
