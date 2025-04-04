#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WebServer.h>
#include <ArduinoJson.h>
#include "SensorPH.h"
#include "MotorDriver.h"

extern WebServer server;
extern float desiredTemperature;
extern bool shouldPumpWater;
extern bool shouldLight;

typedef struct {
    float* temperature;
    float* humidity;
    float* phValue;
} SensorPointers;

void sensorPostHandler();
void handleSensorData();
void setupWebServer();

#endif
