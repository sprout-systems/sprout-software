#include "../include/WebServerHandler.h"

WebServer server(80);

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

void sensorPostHandler() {
    if (server.hasArg("plain")) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, server.arg("plain"));
        
        if (error) {
            server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            return;
        }

        if (doc.containsKey("desiredTemp")) {
            desiredTemperature = doc["desiredTemp"];
            Serial.print("New desired temperature set: ");
            Serial.println(desiredTemperature);
        }

        if (doc.containsKey("LEDStatus")) {
            shouldLight = doc["LEDStatus"];
            Serial.print("LED command: ");
            Serial.println(shouldLight ? "ON" : "OFF");
            if (shouldLight) LedOn(); else LedOff();
        }

        if (doc.containsKey("pumpStatus")) {
            shouldPumpWater = doc["pumpStatus"];
            Serial.print("Water pump command: ");
            Serial.println(shouldPumpWater ? "ON" : "OFF");
            if (shouldPumpWater) {
                pumpWater();
                vTaskDelay(pdMS_TO_TICKS(5000)); 
            }
        }

        server.send(200, "application/json", "{\"status\":\"ok\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"No body received\"}");
    }
}

void setupWebServer() {
    server.on("/sensor", HTTP_POST, sensorPostHandler);
    server.on("/sensor", HTTP_GET, handleSensorData);
    server.begin();
}
