#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "include/SensorDHT.h"
#include "include/SensorPH.h"
//#include "include/LCDDisplay.h"

const char *ssid = "honor1";
const char *password = "";

WebServer server(80);

void handleSensorData() {
    JsonDocument data;
    data["temperature"] = temperature;
    data["humidity"] = humidity;
    data["ph"] = phValue;
    
    String response;
    serializeJson(data, response);
    
    server.send(200, "application/json", response);
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
    server.begin();

    xTaskCreate(ReadDHT_Task, "DHT11", 4096, NULL, 1, NULL);
    xTaskCreate(ReadPH_Task, "PH", 4096, NULL, 1, NULL);
}

void loop() {
    server.handleClient();
    //LCD_Display(temperature, humidity, phValue); 
}
