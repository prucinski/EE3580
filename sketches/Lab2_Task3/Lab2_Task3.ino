#include <EE3580_lab2.h>

int prevRead = -1;

void setup() {
  carrier_62k(128);
  Serial.begin(9600); 
  Serial.println(OCR0A);
  Serial.println(OCR0B);
  }
void loop() {
  int thisRead = analogRead(0);
  //ensuring noise in potentiometer is irrelevant
  if(abs(thisRead - prevRead) > 4){
    uint8_t dutyCycle = thisRead/4;
    //dutyCycle varies from 0 to 255, thisRead from 0 to 1023
    carrier_62k(dutyCycle);
    prevRead = thisRead; 
  }  
  Serial.println(analogRead(1));
  }
