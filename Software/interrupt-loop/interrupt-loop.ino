#include <avr/sleep.h>
#include <avr/wdt.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1 << ADEN))
#define adc_enable()  (ADCSRA |= (1 << ADEN))

// Number of watchdog cycles that make up the main delay
const int wdCount = 5;

// Period for watchdog timer
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms 6=1s, 7=2s , 8=4s , 9=8s
const int wdPeriod = 8;

const int  pwmPin = 0;
const int  ledPin = 1;
const int  buttonPin = 2;
const byte buttonInt = PCINT2;
boolean f_wdt = 1;  // flag for watchdog interrupts
boolean f_btn = 1;  // flag for button interrupts

void flash(int f, int d = 300) {
  for (int i = 0; i < f; i++) {
    digitalWrite(ledPin,HIGH);
    delay(d);
    digitalWrite(ledPin,LOW);
    delay(d);
  }
}

void setup(){
  pinMode(pwmPin,OUTPUT);
  digitalWrite(pwmPin,0);
  
  pinMode(ledPin,OUTPUT);

  // Flash quick sequence so we know setup has started
  flash(2,500);
  delay(500);

  pinMode(buttonPin,INPUT_PULLUP);

  setup_watchdog(wdPeriod);
  setup_pininterrupt(buttonInt);
}

int counter;  // counts watchdog interrupts
bool button;  // flags when debounced button is detected
byte pwmSteps = 5;
byte pwmVal[5] = {0,64,128,192,255};
byte pwm = 0;
void loop(){
  counter = 0;
  button=false;
  while ((counter < wdCount) && !button) {
    system_sleep();
    flash(1,2);       // heartbeat
    if (f_btn) {
      f_btn=false;  // reset flag
      delay(10);    // debounce
      if (!digitalRead(buttonPin)) button = true;
    }
    if (f_wdt) {     // Timed out watchdog
      f_wdt=false;   // reset flag
    }
  }

  if (button) {
    pwm += 1;
    pwm %= pwmSteps;
    flash(pwm+1,250);  // signal that button was pressed
    delay(250);
  }
  if (pwmVal[pwm] == 0) digitalWrite(pwmPin,LOW);
  else analogWrite(pwmPin, pwmVal[pwm]);  // only PWM when needed

  flash(10,30);
}

void system_sleep() {
  adc_disable();
  digitalWrite(ledPin,LOW); // ensure LED stays off
  if (pwm > 0) {
    // PWM is running, dont sleep since that shuts PWM down
    while (!f_btn && !f_wdt) delay(10);
  } 
  else {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();    // Sleep here
    sleep_disable(); 
  }
  adc_enable();
}

void setup_watchdog(int period) {
  byte bitbuf;
  if (period > 9 ) period=9;
  bitbuf=period & 7;
  if (period > 7) bitbuf|= (1<<5);
  bitbuf|= (1<<WDCE);
  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bitbuf;
  WDTCR |= _BV(WDIE);
}

void setup_pininterrupt(int pcint) {
  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(pcint);
}

// Watchdog Interrupt Service 
ISR(WDT_vect) {
  counter++;
  f_wdt=true;  // flag that this was the watchdog
}

// Pin interrupt service
ISR(PCINT0_vect) {
  // ignore unless pin is low
  if (!digitalRead(buttonPin)) f_btn=true;
}
