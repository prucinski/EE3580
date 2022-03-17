  //minimum frequency - 16000000/(256*(255+1)) = 244,1 Hz
 //maximum frequency - 16000000/(256*(1+1)) = 31 250 Hz
  #define MAX_FREQ 31250
  #define MIN_FREQ 244
  
  int prevRead = -1;
  uint8_t dutyCycle = 128;
   

void timer_setup(uint32_t freq, uint8_t duty_cycle)
{

 if(freq < MIN_FREQ || freq > MAX_FREQ){
  return;
 }
 cli();
 // Fast PWM, prescaler 256
 TCCR0A = 0x23;
 // prescaler 256 (0x0C = 256)
 TCCR0B = 0x0C;
 OCR0A = round(16000000/(256*freq) - 1); //how long till reset?
 //This wont work:
 //OCR0B = (duty_cycle/256)*(OCR0A + 1) - 1; //how long wave is on?
 //This will as duty_cycle/256 will not be zero anymore
 OCR0B = (duty_cycle*(OCR0A+1)/256) - 1; 
 DDRD = (1<<PD5);
 sei();
}

void setup() {
  //timer_setup(1000, 128);
  //timer_setup(10000, 64);
  timer_setup(440, 255);
  Serial.begin(9600); 
  Serial.println(OCR0A);
  Serial.println(OCR0B);
  }
void loop() {
  int thisRead = analogRead(0);
  //ensuring noise is irrelevant
  if(abs(thisRead - prevRead) > 4){
    //31 250 / 1024 distinct values = jump of 30.5 Hz + base address
    uint32_t newFreq = thisRead*30 + MIN_FREQ;
    Serial.println("Chosen frequency:");
    Serial.println(newFreq);
    timer_setup(newFreq,dutyCycle);
    prevRead = thisRead; 
    Serial.println("The new values for the registers are:");
    Serial.println(OCR0A);
    Serial.println(OCR0B);
  }
  //Serial.println(analogRead(0));
  }
