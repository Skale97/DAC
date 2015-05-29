
volatile int readFlag;

volatile byte analogVal;
byte val;
void setup() {
  ADMUX &= B11110000;
  ADMUX |= B01100000;
  ADMUX &= B11110000;
  ADCSRA |= B10000000;
  ADCSRA |= B00100000;
  ADCSRB &= B11111000;
  ADCSRA |= B00000111;
  ADCSRA |= B00001000;
  sei();
  readFlag = 0;
  ADCSRA |= B01000000;
  DDRD = DDRD | B11111100;
  DDRB = DDRB | B00000011;
}


// Processor loop
void loop() {

  // Check to see if the value has been updated
  if (readFlag == 1) {
    PORTB = B11111111;
    readFlag = 0;
  }
  val = analogVal;
  //val = val >> 2;
  PORTB = val >> 6;
  PORTD = val << 2;

  // Whatever else you would normally have running in loop().

}


// Interrupt service routine for the ADC completion
ISR(ADC_vect) {
  PORTB = B00000000;
  readFlag = 1;

  analogVal = ADCH;

  ADCSRA |= B01000000;
}
