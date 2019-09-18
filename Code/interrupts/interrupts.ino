//ATtiny low power using interrupt to wake
#include <avr/sleep.h>
#include <avr/interrupt.h>
const int switchPin = 3;
const int statusLED = 2;

void setup() {
    pinMode(switchPin, INPUT);
    pinMode(statusLED, OUTPUT);

    // Flash quick sequence so we know setup has started
    for (int k = 0; k < 5; k++) {
        if (k % 2 == 0) {
            digitalWrite(statusLED, HIGH);
        }
        else {
            digitalWrite(statusLED, LOW);
        }
        delay(250);
    } // for
} // setup

void sleep() {
    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement
    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep
    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on
    sei();                                  // Enable interrupts
} // sleep

ISR(PCINT0_vect) {
    wakeReason = 1 ; // 1== button
    // Handle Button.. 
    // If battpower == low; exit. Nothing to do
    // stop timer interrupts.
    // debounce delay and re-read to check.
    // wait for release
    //  if fullCountdown > 0 ; fullCountdown = 0 ; onCountdown = 0; break // flash LED once, we are in full power mode
    //  if onCountdown > 0 ; fullCountdown == 1800; (1800x8s wakeups); break // flash LED twice we are going to quiet mode
    //  if userpower == half ; set userpower == off ;  onCOuntdown = 1800; fullCountdown = 3600; // flash LED long

    // re-start timer interrupts
}

void loop() {
    wakereason = 0; // Will be set to tell us wether timer of button happened.
    sleep();
    if (wakereason == 1)
    digitalWrite(statusLED, HIGH);
    delay(1000);
    digitalWrite(statusLED, LOW);
}
