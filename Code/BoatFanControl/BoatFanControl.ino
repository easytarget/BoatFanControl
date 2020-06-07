 /* boat fan control

 Reads DHT11 temperature and humidity and Voltage on 
  the BoatFanController, and flashes a LED on the fan pin to
  show the readings

         D5 - Reset pin
         D4 - N/C       (USB-)
  Digi   D3 - Button    (USB-)
  spark  D2 - Vin Sense
         D1 - DHT11     (Onboard LED)
         D0 - Fan PWM

 */
 
// For loop/logic debug use SerialCDC in place of DHT sensor
#define DEVEL

/*-------------------------------*/

#ifdef DEVEL
  #include <DigiUSB.h>
#endif

#include <DHT11.h>
DHT11 dht;

#define FAN_PIN 0  // D0
#define DHT_PIN 1  // D1
#define VCC_PIN 2  // D2 used to set pin mode
#define VCC_APIN 1 // D2 = A1 for analog read
#define BUTTON_PIN 3 

void myDelay(int d) {
  #ifdef DEVEL
    DigiUSB.delay(d);
  #else
    delay(d);
  #endif
}

float readVbatt() 
{
  // Take ADC reading and multiply by a scale factor = (5/1024)*11 = 0.05371
  // From: 0-5v ADC 10 bit reading, and 10k:1k resistor divider
  // Value used here is was double-checked by calibration.

  int res = analogRead(VCC_APIN);
  return res * 0.053; // Vbatt in volts
}

void flashError(void)
{
}
  

/*   SETUP    */

void setup() {                
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  #ifdef DEVEL
    DigiUSB.begin();
    DigiUSB.println(F("Begin.."));
  #endif
  dht.setup(DHT_PIN);
  pinMode(VCC_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
}

/*   LOOP     */

void loop() {
  #ifdef DEVEL
    DigiUSB.print(millis());
    DigiUSB.print(F(" : "));
  #endif

  // Readings
  int temp = dht.getTemperature();
  int humi = dht.getHumidity();
  float vBatt = readVbatt();

  if (strcmp(dht.getStatusString(),"OK") != 0) 
  {
    flashError();
    #ifdef DEVEL
      DigiUSB.print(F("Err : "));
    #endif
  }
  else 
  {
    // Do something with values
    
    #ifdef DEVEL
      // Serial dump results when button pressed
      DigiUSB.print(temp);
      DigiUSB.print(F(" : "));
      DigiUSB.print(humi);
      DigiUSB.print(F(" : "));
    #endif
  } 
  #ifdef DEVEL
    DigiUSB.print(int(vBatt*100));
  #endif

  myDelay(1500);
  #ifdef DEVEL
    DigiUSB.println();
    while (!DigiUSB.available()) myDelay(100);
    DigiUSB.read();
  #endif
  
}
