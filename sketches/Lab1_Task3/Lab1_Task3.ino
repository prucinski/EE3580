#include <EE3580_lab1.h>
#include <stdio.h>

char command[30];
char myBufferCommand[50];
char blinkCommand[] = "blink";
char color[10];
char green[] = "green"; //PB4
char red[] = "red";     //PB5
int noOfBlinks = -1;

void setup() {
 Serial.begin(9600); // initialized the UART
 DDRB = (1<<PB5 | 1<<PB4); // set the direction of PB5 and PB4 as output 
 pinMode(11, INPUT_PULLUP);
}
void loop()
{
 // if blink found,
 getstring(myBufferCommand);
 sscanf(myBufferCommand, "%s %s %d", command, color, &noOfBlinks);
 delay(600);
 int isEqual = strcmp(command, blinkCommand);
 if(isEqual==0){
  Serial.println("Blink command called.");
  if(noOfBlinks >20 || noOfBlinks <0){
    Serial.println("Incorrect number of blinks supplied.");
    return;
  }
  if(strcmp(color,green)==0){
   for(int i = 0; i <noOfBlinks*2; i++){
   PORTB ^= (1<<PB4);
   delay(200);
   }
  }
  else if(strcmp(color, red)==0){
   for(int i = 0; i <noOfBlinks*2; i++){
   PORTB ^= (1<<PB5);
   delay(200);
   }
  }
  else{
    Serial.println("Incorrect color supplied.");
    return;
  }
 }
}
