#ifndef EE3580_lab1_h
#define EE3580_lab1_h

void getstring(char* buffer)
{
char c = 0;
int i = 0;
    while (c != '\r')
    {
        if (Serial.available()) {
            c = Serial.read();
            buffer[i] = c;
            i++;
        }
    }
    buffer[i-1] = 0;
}


// Enables the timer to generate in IRQ every 1 ms
void setup_timer() {
   cli(); // Disable all the interrupts 
   TCCR2A = 0x02;    // CTC mode
   TCCR2B = 0x04;    // Set the prescaler to N=64
   OCR2A = 249;      // Set the threshold to 250 counts
   TIMSK2 = (1<<OCIE2A); // Enable IRQ on Compare Match 
   sei(); // Enable all the interrupts
}


#endif
