#include <WiFi.h>
#include "include/WebServerHandler.h"
#include "include/MotorDriver.h"
#include "include/LCDDisplay.h"

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
    initializeWaterPump();
    initializeLED();
    fanOn();

    xTaskCreate(desiredTemperatureSetTask, "desiredTemperatureSetTask", 2048, NULL, 1, NULL);
    xTaskCreate(ledTask, "LEDToggleTask", 2048, NULL, 1, NULL);
    xTaskCreate(pumpTask, "PumpControlTask", 2048, NULL, 1, NULL);
    xTaskCreate(ReadDHT_Task, "DHT11", 2048, NULL, 1, NULL);
    xTaskCreate(ReadPH_Task, "PH", 2048, NULL, 1, NULL);
    xTaskCreate(LCD_Display, "LCD", 4096, NULL, 1, NULL);
    xTaskCreate(temperatureControl, "MotorDriver", 4096, NULL, 1, NULL);
}

void loop() {
    server.handleClient();
}
