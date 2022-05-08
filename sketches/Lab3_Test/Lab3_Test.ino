int button;
int led;
int buzzer;
int thermistor;

void setup() {
  // put your setup code here, to run once:
  // PB1 (pin 9) - button. PB0 (pin 8) - LED. 
  //PD5 (pin 5) - BUZZER. ADC0 (A0) - thermistor.
  buzzer = 5;
  led = 8;
  button = 9;
  thermistor = A0;

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  //no need for pinMode for thermistor 

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  tone(buzzer, 100);
  Serial.println(analogRead(thermistor));
  if(digitalRead(button) == HIGH){
    digitalWrite(led, LOW);
  }
  else{
    digitalWrite(led, HIGH);
  }

}
