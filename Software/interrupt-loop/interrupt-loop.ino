#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

const int pinLed = 1;
const int switchPin = 3;

volatile boolean f_wdt = 1;
volatile boolean f_btn = 1;
int counter = 0;

void setup(){
  pinMode(pinLed,OUTPUT);
  // Flash quick sequence so we know setup has started
  for (int k = 0; k < 6; k++) {
      if (k % 2 == 0) {
          digitalWrite(pinLed, HIGH);
      }
      else {
          digitalWrite(pinLed, LOW);
      }
      delay(200);
  }
  delay(300);

  pinMode(switchPin,INPUT_PULLUP);

  setup_watchdog(8);
  setup_pininterrupt();
}

void loop(){
  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=false;       // reset flag
    f_btn=false;       // reset flag
    pinMode(pinLed,INPUT); // set led port to intput to save power
    system_sleep();
    pinMode(pinLed,OUTPUT); // set led port back to output
    // heartbeat
    digitalWrite(pinLed,HIGH);
    delay(10); 
    digitalWrite(pinLed,LOW);

    if (f_btn) {
      for (int k = 0; k < 10; k++) {
        if (k % 2 == 0) {
          digitalWrite(pinLed, HIGH);
        }
        else {
          digitalWrite(pinLed, LOW);
        }
        delay(50);
      }
      delay(300);  
    }
    
    // Counter only incremented when watchdog fires, no need to test the wake reason
    if (counter > 4) {           // 5*4s cycles == 20s
      digitalWrite(pinLed,HIGH);
      delay(500); 
      digitalWrite(pinLed,LOW);
      delay(500);
      digitalWrite(pinLed,HIGH);
      delay(500);
      digitalWrite(pinLed,LOW);
      counter = 0;
    }
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

void setup_watchdog(int ii) {
  // 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
  // 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec

  byte bb;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

void setup_pininterrupt() {
  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(PCINT3);
}

// Watchdog Interrupt Service 
ISR(WDT_vect) {
  counter++;
  f_wdt=true;  // set global flag
}

// Pin interrupt service
ISR(PCINT0_vect) {
  f_btn=true;  // set global flag
}
