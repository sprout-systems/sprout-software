#include "../include/MotorDriver.h"

void initializeMotorDriver() {
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    digitalWrite(ENA, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void peltierCooling() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(ENA, HIGH);
}

void peltierHeating() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENA, HIGH);
}

void peltierOff() {
    digitalWrite(ENA, LOW);
}

void fanOn() {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(ENB, HIGH);
}

void temperatureControl(void* pvParameters){
    temperaturePointers* temperature = (temperaturePointers*)pvParameters;

    while(1){
        if(*temperature->currentTemperature < *temperature->desiredTemperature){
            peltierCooling();
        } else if(*temperature->currentTemperature > *temperature->desiredTemperature){
            peltierHeating();
        } else {
            peltierOff();
        }
    }
}
