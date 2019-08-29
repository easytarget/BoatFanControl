#include <DigiCDC.h> // Remove at the end of days...

// Some Hardware
#define FAN_PIN 0 
#define VCC_PIN 2
#define VCC_APIN 1 // digital pin 2 == Analog pin 1

void setup() {                
  // initialize the IO pins as needed.
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  pinMode(VCC_PIN,INPUT);
  
  // USB Serial Lib for DEBUG!
  SerialUSB.begin(); 
  // Wait for input
  while (!SerialUSB.available()) SerialUSB.delay(100);
  // Dump a welcome
  SerialUSB.println(F("See your stuff here:"));
  SerialUSB.delay(100);

  
}

float readVbatt() 
{
  int res = analogRead(VCC_APIN);
  SerialUSB.print("Raw: ");
  SerialUSB.print(res);
  SerialUSB.print(" : Vbatt: ");
  // maths: (5/1024)*11 = 0.05371 ; 0-5v 10bit resolution, 10k:1k resistor divider
  // Experimentation: use factor of 0.053 ; maths from above + calibration.
  return res * 0.053; // Vbatt in volts
}

// the loop routine runs over and over again forever:

long lastVcc = -1;
byte statusLED = 0;

void loop() {
  // Flash LED once per second.
  SerialUSB.delay(500);        // keep usb alive during delay.
  analogWrite(FAN_PIN,statusLED);
  if (statusLED == 255) 
  {
    statusLED = 0;
  } 
  else
  {
    statusLED = 255;
    SerialUSB.println(readVbatt());
  }
}
