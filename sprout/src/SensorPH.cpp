#include "../include/SensorPH.h"

unsigned long int avgValue;  
int buf[10];
int temp;
float phValue = 0.0;

void ReadPH_Task(void *pvParameters) {  
  pinMode(PHSensor, OUTPUT);  
  Serial.begin(115200);

  while (1) {
      for(int i=0;i<10;i++){ 
          buf[i]=analogRead(PHSensor);
          delay(10);
      }
      for(int i=0;i<9;i++){
          for(int j=i+1;j<10;j++){
            if(buf[i]>buf[j]){
                temp=buf[i];
                buf[i]=buf[j];
                buf[j]=temp;
            }
          }
      }
      avgValue = 0;
      for (int i = 2; i < 8; i++) {                      
          avgValue += buf[i];
      }

      phValue = (float)avgValue * 5.0 / 4096 / 6; 
      phValue = 3.5 * phValue;        

      Serial.print("pH: ");  
      Serial.println(phValue, 2);

      digitalWrite(PHSensor, HIGH);       
      delay(800);
      digitalWrite(PHSensor, LOW);

      vTaskDelay(pdMS_TO_TICKS(2000)); 
  }
}

