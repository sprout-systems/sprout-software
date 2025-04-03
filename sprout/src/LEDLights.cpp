#include "../include/LEDLights.h"

void initializeLED() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void OnLED() {
  Serial.println("Turning ON LED");  
  digitalWrite(LED, HIGH);
}

void OffLED() {
  Serial.println("Turning Off LED");  
  digitalWrite(LED, LOW);
}
