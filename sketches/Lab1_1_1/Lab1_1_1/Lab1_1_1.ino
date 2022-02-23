void setup() {
 DDRB = (1<<PB4); // set the direction of PB5 as output
}
void loop()
{
 PORTB ^= (1<<PB4); // toggle PB5 using a XOR mask
 delay(500);
}
