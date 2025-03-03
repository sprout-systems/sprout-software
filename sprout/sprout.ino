#include "include/DHT.h"

void setup() {
  xTaskCreate(DHT_Task, "DHT11", 256, NULL, 1, NULL);
  vTaskStartScheduler(); 
}

void loop() {
  
}