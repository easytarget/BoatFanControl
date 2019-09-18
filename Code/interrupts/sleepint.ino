#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int pinLed = 0;
int trig = 2;
int heart = 1;
volatile boolean f_wdt = 1;
int counter = 0;

void setup(){
  pinMode(pinLed,OUTPUT);
  pinMode(heart,OUTPUT);
  pinMode(trig,INPUT);
  setup_watchdog(8); // approximately 4 seconds sleep
}

void loop(){
  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;       // reset flag
  if (counter > 192){ //timer to reset approx 15 min
    digitalWrite(pinLed,HIGH);
    delay(500); // Wait for trigger high until set back to sleep
    while(!digitalRead(trig)){delay(500);}
    digitalWrite(pinLed,LOW);
    counter = 0;
  }
  // Show heartbeat uncomment to show blink
  //digitalWrite(heart,HIGH);
  //delay(200);
  //digitalWrite(heart,LOW );
  pinMode(pinLed,INPUT); // set all used port to intput to save power
  system_sleep();
  pinMode(pinLed,OUTPUT); // set all ports into state before sleep
  }

}

// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {
  byte bb;
  //int ww; ? junk?
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  //ww=bb; ? junk ?
  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  counter++;
  f_wdt=1;  // set global flag
}
