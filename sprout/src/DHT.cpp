#include "../include/DHT.h"

DHT dht(DHTPIN, DHTTYPE);

void DHT_Task(void *pvParameters) {  
  dht.begin();
  Serial.begin(115200);

  while (1) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" °C, Humidity: ");
      Serial.print(hum);
      Serial.println(" %");
      Serial.println(uxTaskGetStackHighWaterMark(NULL));
    }
    vTaskDelay(pdMS_TO_TICKS(2000)); 
  }
}
