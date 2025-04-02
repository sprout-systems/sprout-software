#include "../include/WaterPump.h"

void initializeWaterPump() {
  pinMode(WaterPump, OUTPUT);
  digitalWrite(WaterPump, LOW);
}

void pumpWater(void *pvParameters) {
  Serial.println("Turning ON Pump");  
  digitalWrite(WaterPump, HIGH);

  vTaskDelay(pdMS_TO_TICKS(2000)); 

  Serial.println("Turning OFF Pump");
  digitalWrite(WaterPump, LOW);
}

