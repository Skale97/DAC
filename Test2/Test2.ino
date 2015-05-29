
byte sine[] = {128,143,159,174,189,202,215,226,235,243,249,253,255,255,253,249,243,235,226,215,202,189,174,159,143,128,112,96,81,66,53,40,29,20,12,6,2,0,0,2,6,12,20,29,40,53,66,81,96,112,
};
volatile byte analogVal;
volatile int readFlag;
volatile int pos;
volatile long period;
void setup() {
  cli();//stop interrupts

  DDRD = DDRD | B11111100;
  DDRB = DDRB | B00000011;
  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  ADMUX = 0;
  ADCSRA = 0;
  ADCSRB = 0;
  ADMUX |= B01100000;
  ADCSRA |= B10001100;
  ADCSRA |= B01000000;
  sei();
}

void loop() {
  OCR0A = analogVal;
}

ISR(ADC_vect) {
  analogVal = ADCH;
}

ISR(TIMER0_COMPA_vect) {
  if (pos == 50)pos = 0;
  pos++;
  PORTB = sine[pos] >> 6;
  PORTD = sine[pos] << 2;
  ADCSRA |= B01000000;
}
//1,575us period  634,92kHz Sample rate


