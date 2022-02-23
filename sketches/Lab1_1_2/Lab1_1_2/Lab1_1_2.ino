void setup() {
 Serial.begin(9600); // initialized the UART
 pinMode(11, INPUT_PULLUP);
}
void loop()
{
 // Print on the serial line the content
 // the PINB register opportunely masked
 Serial.println(PINB & (1<<PB3));
 delay(500);
}
