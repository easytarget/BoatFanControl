#include <DigiCDC.h> // Remove at the end of days...

// Some Hardware
#define LAMP 0   // Lamp Mosfet
#define LED 1    // Status LED
#define PANEL 2  // Solar panel voltage sense physical pin
#define PANELREAD 1  // Solar panel voltage sense Analog pin
#define BUTTON 3 // Button


void setup() {                
  // initialize the IO pins as needed.
  pinMode(LED,OUTPUT);
  analogWrite(LED,0);
  pinMode(LAMP,OUTPUT);
  analogWrite(LAMP,0);
  pinMode(PANEL,INPUT);
  pinMode(BUTTON,INPUT);
  
  
  // USB Serial Lib for DEBUG!
  SerialUSB.begin(); 
  // Wait for input
  while (!SerialUSB.available()) SerialUSB.delay(100);
  // Dump a welcome
  SerialUSB.println(F("See your shit here:"));
  SerialUSB.delay(100);
}

byte statusLED = 0;

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  ADMUX = _BV(MUX3) | _BV(MUX2);
  SerialUSB.delay(2); // Wait for Vref to settle
  
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)) SerialUSB.refresh(); // measuring (can /remove/ the delay here once serial disabled)
 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH 
  uint8_t high = ADCH; // unlocks both
 
  long result = (high<<8) | low;
 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

long readVpanel() {
  // set to the 1.1 vref
  analogReference(INTERNAL); // ensure we are using internal reference
  SerialUSB.delay(2); // Wait for Vref to settle

  long result = analogRead(PANELREAD);
 
  //result = result * 1.0742; // 1024=1100mV
  result = result * 119.24; // 1024=1100mV but also add the 1:111 resistor divider
  return result; // Vcc in millivolts
}

// the loop routine runs over and over again forever:
long lastVcc = -1;
void loop() {
  // Invert LED once per second.
  SerialUSB.delay(1000);               // keep usb alive // can also use SerialUSB.refresh();
  analogWrite(LED,statusLED);
  analogWrite(LAMP,statusLED/4);
  if (statusLED == 255) 
  {
    statusLED = 0;
    //lastVcc=readVcc();
  } else {
    statusLED = 255;
    //SerialUSB.print(lastVcc);
    //SerialUSB.print(F(" : "));
    SerialUSB.print(readVpanel());
    SerialUSB.print(F(" : "));
    SerialUSB.println(digitalRead(BUTTON));
  }
}
