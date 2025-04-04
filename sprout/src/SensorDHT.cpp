#include "../include/SensorDHT.h"

DHT dht(DHTPIN, DHTTYPE);

float temperature = 0;
float humidity = 0;

void ReadDHT_Task(void *pvParameters) {  
  dht.begin();
  Serial.begin(115200);

  while (1) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °C, Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    }
    vTaskDelay(pdMS_TO_TICKS(2000)); 
  }
}
