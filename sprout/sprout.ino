#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "include/SensorDHT.h"
#include "include/SensorPH.h"
#include "include/LCDDisplay.h"
#include "include/MotorDriver.h"
#include "include/WaterPump.h"

float desiredTemperature = 25;
bool shouldPumpWater = false; 

SensorPointers sensorPtrs = {
    &temperature,
    &humidity,
    &phValue
};

temperaturePointers temperaturePtrs  = {
    &desiredTemperature,
    &temperature
};

const char *ssid = "honor";
const char *password = "";

WebServer server(80);

void handleSensorData() {
    JsonDocument data;
    data["temperature"] = temperature;
    data["humidity"] = humidity;
    data["ph"] = phValue;
    data["desiredTemp"] = desiredTemperature;
    data["pumpStatus"] = shouldPumpWater;

    String response;
    serializeJson(data, response);
    
    server.send(200, "application/json", response);
} 

void handleCommand(void *pvParameters) {
    if (server.hasArg("plain") {
        JsonDocument doc;
        deserializeJson(doc, server.arg("plain"));
        
        if (doc.containsKey("desiredTemp")) {
            desiredTemperature = doc["desiredTemp"];
            Serial.print("New desired temperature set: ");
            Serial.println(desiredTemperature);
        }
        
        if (doc.containsKey("pumpWater")) {
            shouldPumpWater = doc["pumpWater"];
            Serial.print("Water pump command: ");
            Serial.println(shouldPumpWater ? "ON" : "OFF");
            
            if (shouldPumpWater) {
                pumpWater();
                while (!shouldPumpWater) {
                    vTaskDelay(pdMS_TO_TICKS(5000)); 
                }
            }
        }
        server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"No data received\"}");
    }
}

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(10000);
        Serial.println("Connecting to WiFi...");
    }
    
    Serial.println("Connected to WiFi");

    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/sensor", HTTP_GET, handleSensorData);
    server.on("/command", HTTP_POST, handleCommand);
    server.begin();

    initializeMotorDriver();
    initializeWaterPump();
    fanOn();

    xTaskCreate(handleCommand, "handleCommand", 2048, NULL, 1, NULL);
    xTaskCreate(ReadDHT_Task, "DHT11", 2048, NULL, 1, NULL);
    xTaskCreate(ReadPH_Task, "PH", 2048, NULL, 1, NULL);
    xTaskCreate(LCD_Display, "LCD", 4096, &sensorPtrs, 1, NULL);
    xTaskCreate(temperatureControl, "MotorDriver", 4096, &temperaturePtrs, 1, NULL);
}

void loop() {
    server.handleClient();
}
