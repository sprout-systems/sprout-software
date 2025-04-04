#include "../include/MotorDriver.h"

void initializeMotorDriver() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(IN5, OUTPUT);
    pinMode(IN6, OUTPUT);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}

void peltierCooling() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void peltierHeating() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void peltierOff() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void fanOn() {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void temperatureControl(void* pvParameters) {
    temperaturePointers* temperature = (temperaturePointers*)pvParameters;

    while (1) {
        float* currentTemp = temperature ? temperature->currentTemperature : nullptr;
        float* desiredTemp = temperature ? temperature->desiredTemperature : nullptr;

        if (!currentTemp || !desiredTemp) {
            Serial.println("Temperature pointers not set");
            vTaskDelay(1000 / portTICK_PERIOD_MS);  
            continue;
        }

        if (*currentTemp - 0.5 > *desiredTemp) {
            peltierCooling();
            Serial.println("Cooling");
        } else if (*currentTemp + 0.5 < *desiredTemp) {
            peltierHeating();
            Serial.println("Heating");
        } else {
            peltierOff();
            Serial.println("Off");
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);  
    }
}

void pumpOn() {
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
}

void pumpOff() {
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
}

void pumpWater() {
  Serial.println("Turning ON Pump");  
  pumpOn();

  vTaskDelay(pdMS_TO_TICKS(2000)); 

  Serial.println("Turning OFF Pump");
  pumpOff();
}

void LedOn() {
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
}

void LedOff() {
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}
