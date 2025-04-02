#ifndef WATER_PUMP_H
#define WATER_PUMP_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define WaterPump 16
//16 -> in+
//gnd -> in-
//com -> 5v 
//no -> pump(+)
//gnd -> pump(-)

void pumpWater(void *pvParameters);
 
#endif
