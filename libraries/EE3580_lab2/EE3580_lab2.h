
#ifndef _EE3580_lab2
#define _EE3580_lab2

#define BASE_FREQ   62500UL
#define MIN_FREQ        245

void lut_setup_triangular(uint8_t* wave) {
int i;

    for(i=0; i<128; i++)
        wave[i] = 2*i;
        
    for(i=128; i<256; i++)
        wave[i] = 511-2*i;
}

void lut_setup_sawtooth(uint8_t* wave) {
int i;

    for(i=0; i<256; i++){
        wave[i] = i;
	}
}

void lut_setup_sinusoidal(uint8_t* wave) {
double i;

    for(i=0; i<256; i++){
        //wave[i] = 256*sin((i/256)*2*pi);
}

}



void timer_setup(uint32_t freq, uint8_t duty_cycle)
{
uint32_t x;

     // check that the frequency in the correct range
     if (freq>BASE_FREQ || freq<MIN_FREQ)
         return;
     
     cli();
     // Fast PWM, prescaler 256
     TCCR0A = 0x23;
     TCCR0B = 0x0C;

     x = round(BASE_FREQ/freq);
     
     OCR0A = x - 1;
     OCR0B = ((x*duty_cycle)>>8) - 1;
     
     DDRD = (1<<PD5);
     sei();
}


void carrier_62k(uint8_t duty_cycle) 
{  
     cli();
     // Fast PWM, prescaler 256
     TCCR0A = 0x23;
     TCCR0B = 0x09;
       
     OCR0A = 0xFF;
     OCR0B = duty_cycle;
     
     DDRD = (1<<PD5);
     sei();
}

void timer1_setup() {
    cli();    
    TCCR1A = 0x00;
    TCCR1B = 0x01 | (1 << WGM12);
    OCR1A = 0x7D0;
    TIMSK1 = (1<<OCIE1A);
    sei();
}

#endif