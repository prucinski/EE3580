#include <EE3580_lab1.h>
#include <stdio.h>

char command[30];
char myBufferCommand[50];
char blinkCommand[] = "blink";
char printCommand[] = "print";

//globals for interrupt routine
long int timer;
long int timestampArray[10];
int currentIndex = 0;
int previousButton = 8;
int currentButton;
bool isCircular = false;

char color[10];
char green[] = "green"; //PB4
char red[] = "red";     //PB5
int noOfBlinks = -1;

ISR(TIMER2_COMPA_vect){
  timer++;
  currentButton = (PINB & (1<<PB3));
  //transition on FALLING EDGE (e.g. moment it's pressed, not moment it's let go)
  if(currentButton - previousButton < 0){
    if(currentIndex ==10){
      currentIndex=0;
      //if is circular, we have to keep that in mind when we're printing.
      isCircular = true;
    }
    timestampArray[currentIndex] = timer;
    currentIndex+=1;
  }
  previousButton = currentButton;
  
}

void setup() {
 Serial.begin(9600); // initialized the UART
 DDRB = (1<<PB5 | 1<<PB4); // set the direction of PB5 and PB4 as output 
 pinMode(11, INPUT_PULLUP); //NO EXTERNAL PULLUP RESISTOR.
 setup_timer();
}
void loop()
{
 // if blink found,
 getstring(myBufferCommand);
 sscanf(myBufferCommand, "%s %s %d", command, color, &noOfBlinks);
 delay(600);
 int isEqualBlink = strcmp(command, blinkCommand);
 if(isEqualBlink==0){
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
  int isEqualPrint = strcmp(command, printCommand);
  if(isEqualPrint == 0){
    //If array is circular, we have to print all 10 entries
    //and know when to "reset" the counter.
    if(isCircular){
    for(int i =0; i < 10; i++){
      currentIndex+=1;
      Serial.print(timestampArray[currentIndex-1]);
      Serial.print("      ");

      if(currentIndex == 10){
        currentIndex = 0;
      }
      }
      Serial.println("");
    }
    //Array is not circular. Print as usual.
    else{
      for(int i =0; i < currentIndex; i++){
        Serial.print(timestampArray[i]);
        Serial.print("      ");
      }
      Serial.println("");   
    }
    
  }
}
