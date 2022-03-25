#include <EE3580_lab2.h>
int prevRead = 0;
long int time = 0;
uint8_t wave[256]; // Look up table
uint16_t index, stepsize; // index and stepsize
uint32_t waveformFrequency; //making it 32 bit allows for operating on higher numbers temporarily.
uint16_t selectIndex;

void setup() {
  //start frequency at max frequency
  waveformFrequency = 256;
  index = 0;
  stepsize = 1;
  //lut_setup_triangular(wave);
  //lut_setup_sawtooth(wave);
  lut_setup_sinusoidal(wave);
  //setup of the "square wave". It doesn't mnatter
  //what wave there is as we are only extracting the
  //DC component anyway.
  carrier_62k(128);
  //setting up the interrupt for updating OCR0B
  timer1_setup();
  Serial.begin(19200); 


  }

ISR(TIMER1_COMPA_vect){
  time++;
  //stepsize = freq(in fixed point) * 32 ms (in fixed point) bit shifted right by 8. If we had higher frequencies, there'd
  //generally be much more wiggle room, but my highest frequency is 1Hz, so not a lot of stepsizes (1-4).
  stepsize = ((waveformFrequency * ((32<<8)/1000))>>8) + 1;
  //select the index
  int selectIndex = index>>8;
  OCR0B = wave[selectIndex];
  index+=stepsize;
  if(selectIndex>255){
    index = 0;
  }
}
void loop() {
  int thisRead = analogRead(0);
  //ensuring noise in potentiometer is irrelevant
  if(abs(thisRead - prevRead) > 4){
    //turn potentiometer into fixed-point representation,
    //with max being 1.024 Hz (Because it's the easiest ;))
    waveformFrequency = thisRead>>3;   
  }
  if(time%100 == 0){
    Serial.println(analogRead(1));
  }
  }
