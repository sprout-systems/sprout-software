#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WebServer.h>
#include <ArduinoJson.h>
#include "LEDLights.h"
#include "WaterPump.h"
#include "SensorDHT.h"
#include "SensorPH.h"

extern WebServer server;

void desiredTemperatureSetTask(void *pvParameters);
void ledTask(void *pvParameters);
void pumpTask(void *pvParameters);
void handleSensorData();
void setupWebServer();

#endif

