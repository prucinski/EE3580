#include <EE3580_lab2.h>
int prevRead = 0;
long int time = 0;
uint8_t wave[256]; // Look up table
uint16_t index, stepsize; // index and stepsize

void setup() {
  index = 0;
  stepsize = 1;
  lut_setup_triangular(wave);
  timer1_setup();
  Serial.begin(9600); 
  }

ISR(TIMER1_COMPA_vect){
  time++;
  OCR0B = wave[index];
  index+=stepsize;
  if(index>256){
    index = 0;
  }
}
void loop() {
  int thisRead = analogRead(0);
  //ensuring noise in potentiometer is irrelevant
  if(abs(thisRead - prevRead) > 4){
     
  }  
  if(time){
    Serial.println(analogRead(1));
  }
  }
