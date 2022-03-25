#include <stdio.h>
#include <time.h>
//globals for interrupt routine
long int timer;
long int timestampBuffer[256];
int currentIndex = 0; //keeping track of the position of the array we're in right now
int previousButton = 0;
int currentButton;
bool isCircular = false;
bool poll;
void print_buffer();

//part i)
void button_pressed(){
  //if we found ourselves at the end of the array, make it circular.

  //glithc prevention - ignore if less than 100ms passed between presses
  if(currentIndex!=0){
    if(timer - timestampBuffer[currentIndex -1] < 100){
      return;
  }
  }

  if(currentIndex ==256){
      currentIndex=0;
      //if is circular, we have to keep that in mind when we're printing.
      isCircular = true;
    }
    timestampBuffer[currentIndex] = timer;
    currentIndex+=1;
    print_buffer();
}

//part iii). Interrupt to check if button was pressed.
//it is called almost precisely every millisecond.
ISR(TIMER2_COMPA_vect){
  timer++;
  currentButton = digitalRead(PD2);
  //transition on FALLING EDGE (e.g. moment it's pressed, not moment it's let go)
  if(currentButton - previousButton < 0){
    button_pressed();
  }
  previousButton = currentButton;
}

//Shamelessy taken from the Lab 1 library ;)
// Enables the timer to generate in IRQ every 1 ms
void setup_timer() {
   cli(); // Disable all the interrupts 
   TCCR2A = 0x02;    // CTC mode
   TCCR2B = 0x04;    // Set the prescaler to N=64
   OCR2A = 249;      // Set the threshold to 250 counts
   TIMSK2 = (1<<OCIE2A); // Enable IRQ on Compare Match 
   sei(); // Enable all the interrupts
}
void setup_polling(bool isPolled){
   poll = isPolled;
}
void print_buffer(){
    //If array is circular, we have to print all 256 entries
    //and know when to "reset" the counter.
    if(isCircular){
    for(int i =0; i < 256; i++){
      currentIndex+=1;
      Serial.print(timestampBuffer[currentIndex-1]);
      Serial.print("      ");
      if(i%10==0){
        Serial.println("");
      }

      if(currentIndex == 256){
        currentIndex = 0;
      }
      }
      Serial.println("");
      Serial.println("");
    }
    //Array is not circular. Print as usual.
    else{
      for(int i =0; i < currentIndex; i++){
        Serial.print(timestampBuffer[i]);
        Serial.print("      ");
        //make it readable in serial
        if(i%10 == 0 && i!=0){
          Serial.println("");
        }

      }
      Serial.println("");
      Serial.println("");    
    }
    
}
void setup() {
 Serial.begin(9600); // initialized the UART
 pinMode(PD2, INPUT_PULLUP); //NO EXTERNAL PULLUP RESISTOR.
 //FOR POLLING METHOD, PASS TRUE.
 //FOR INTERRUPT METHOD, PASS FALSE.
 setup_polling(false);
 if(!poll){
  setup_timer();
  Serial.println("Interrupt timer set.");
 }
 else{
  Serial.println("Polling timer set.");
  }
}
void loop()
{
//poll on every iteration to check for a button press.
  if(poll){
    currentButton = digitalRead(PD2);
    //transition on FALLING EDGE (e.g. moment it's pressed, not moment it's let go)
    if(currentButton - previousButton < 0){
      timer = millis();
      button_pressed();    
    }
  previousButton = currentButton;
  }
//if interrupts are used, no code is necessary.
}
