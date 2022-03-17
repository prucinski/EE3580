void timer_setup()
{
 cli();
 // Fast PWM, prescaler 256
 TCCR0A = 0x23;
 // prescaler 256 (0x0C = 256)
 TCCR0B = 0x0C;
 OCR0A = 141;
 OCR0B = 107;
 DDRD = (1<<PD5);
 sei();
}

void setup() {
  timer_setup();
  Serial.begin(9600); 
  }
void loop() { 
  Serial.println(analogRead(0));
  }
