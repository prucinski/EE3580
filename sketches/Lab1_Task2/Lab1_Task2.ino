#include <EE3580_lab1.h>

char command[255];
char blinkCommand[] = "blink";

void setup() {
 Serial.begin(9600); // initialized the UART
 DDRB = (1<<PB5 | 1<<PB4); // set the direction of PB5 and PB4 as output 
 pinMode(11, INPUT_PULLUP);
}
void loop()
{
 // if blink found,
 getstring(command);
 delay(600);
 int isEqual = strcmp(command, blinkCommand);
 if(isEqual==0){
  Serial.println("Blink command called.");
  for(int i = 0; i <20; i++){
   //Serial.println(((1<<PB5) + (1<<PB4)));
   PORTB ^= (1<<PB5 | 1<<PB4);
   delay(200);
  }
 }
}
