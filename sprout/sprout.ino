#include <WiFi.h>
#include "include/WebServerHandler.h"

float desiredTemperature = 25;
bool shouldPumpWater = false; 
bool shouldLight = false; 
 
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

    setupWebServer();  

    initializeMotorDriver();
    fanOn();

    xTaskCreate(ReadDHT_Task, "DHT11", 4096, NULL, 1, NULL);
    xTaskCreate(ReadPH_Task, "PH", 4096, NULL, 1, NULL);
    xTaskCreate(temperatureControl, "MotorDriver", 4096, &temperaturePtrs, 1, NULL);
}

void loop() {
    server.handleClient();
}
