#ifndef LED_LIGHTS_H
#define LED_LIGHTS_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED 4 
//16 -> in+
//gnd -> in-
//com -> 5v 
//no -> LED(+)
//gnd -> LED(-)

void initializeLED();
void OnLED();
void OffLED();
 
#endif
