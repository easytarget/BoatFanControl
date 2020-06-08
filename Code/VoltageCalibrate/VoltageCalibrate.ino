#include <DigiUSB.h> // Remove at the end of days...

// Some Hardware
#define FAN_PIN 0 
#define VCC_PIN 2
#define VCC_APIN 1 // digital pin 2 is also analog pin 1

// Store result
int res[30];

void setup() {                
  // initialize the IO pin
  pinMode(VCC_PIN,INPUT);
  DigiUSB.begin();
}

// the loop routine runs over and over again forever:
float target = 11;

void loop() {
  DigiUSB.println();
  DigiUSB.println();
  DigiUSB.print(F("Set Vin to: "));
  DigiUSB.print(target);
  DigiUSB.println(F(" volts and send anything to begin"));
   // Wait for input
  while (!DigiUSB.available()) DigiUSB.delay(100);
  while (DigiUSB.available()) DigiUSB.read();   // chomp buffer

  for (int i=0; i < 30; i++) {
    DigiUSB.delay(200);
    res[i] = analogRead(VCC_APIN);
    DigiUSB.print(res[i]);
    DigiUSB.print(F(", "));
    if (i%10 == 9) DigiUSB.println();
  }
  double tot=0;
  int max=0;
  int min=1024;
  for (int i=0; i < 30; i++) {
    DigiUSB.refresh();
    tot+=res[i];
    if (res[i] < min) min=res[i];
    if (res[i] > max) max=res[i];
  }
  if (tot == 0) {
    DigiUSB.println(F("** No readings recorded, check wiring **"));
    return;
  }
  DigiUSB.print(F("Max: "));
  DigiUSB.println(max);
  DigiUSB.print(F("Min: "));
  DigiUSB.println(min);
  tot = tot-max-min;
  double avg = tot/28;
  double factor = float(target)/avg;
  DigiUSB.print(F("Average: "));
  DigiUSB.print(avg,4);  
  DigiUSB.println();
  DigiUSB.print(F("Scale factor: "));
  DigiUSB.print(factor,4);  
  DigiUSB.println();
}
