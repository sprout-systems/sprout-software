#include "../include/WebServerHandler.h"

float desiredTemperature = 25;
bool shouldPumpWater = false; 
bool shouldLight = false; 

WebServer server(80);

void desiredTemperatureSetTask(void *pvParameters) {
    while (1) {
        if (server.hasArg("plain")) {
            JsonDocument doc;
            deserializeJson(doc, server.arg("plain"));

            if (doc.containsKey("desiredTemp")) {
                desiredTemperature = doc["desiredTemp"];
                Serial.print("New desired temperature set: ");
                Serial.println(desiredTemperature);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void ledTask(void *pvParameters) {
    while (1) {
        if (server.hasArg("plain")) {
            JsonDocument doc;
            deserializeJson(doc, server.arg("plain"));

            if (doc.containsKey("LEDStatus")) {
                shouldLight = doc["LEDStatus"];
                Serial.print("LED command: ");
                Serial.println(shouldLight ? "ON" : "OFF");

                if (shouldLight) {
                    OnLED();
                } else {
                    OffLED();
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void pumpTask(void *pvParameters) {
    while (1) {
        if (server.hasArg("plain")) {
            JsonDocument doc;
            deserializeJson(doc, server.arg("plain"));

            if (doc.containsKey("pumpStatus")) {
                shouldPumpWater = doc["pumpStatus"];
                Serial.print("Water pump command: ");
                Serial.println(shouldPumpWater ? "ON" : "OFF");

                if (shouldPumpWater) {
                    pumpWater();
                    vTaskDelay(pdMS_TO_TICKS(5000)); 
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void handleSensorData() {
    JsonDocument data;
    data["temperature"] = temperature;
    data["humidity"] = humidity;
    data["ph"] = phValue;
    data["desiredTemp"] = desiredTemperature;
    data["pumpStatus"] = shouldPumpWater;
    data["lightStatus"] = shouldLight;

    String response;
    serializeJson(data, response);
    
    server.send(200, "application/json", response);
} 

void setupWebServer() {
    server.on("/sensor", HTTP_GET, handleSensorData);
    server.on("/command", HTTP_POST, handleCommand);
    server.begin();
}
