#ifndef SENSOR_PH_H
#define SENSOR_PH_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

//https://adiy.in/shop/ph-sensor-module-with-ph-probe/?srsltid=AfmBOoqSywxQt5d4BLzf7yZyjeVPPq1E3dZPVNfRSS9YeZorFWx3eKjU
#define PHSensor 32 

extern float phValue;

void ReadPH_Task(void *pvParameters);

#endif
