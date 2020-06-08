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
 
// For loop/logic debug use DigiUSB in place of DHT sensor
#define DEVEL

/*-------------------------------*/

#ifdef DEVEL
  #include <DigiUSB.h>
#endif

#define FAN_PIN 0
#define DHT_PIN 1
#define VIN_PIN 2
#define VIN_APIN 1 // digital pin 2 is also analog pin 1
#define BUTTON_PIN 3 

#define CYCLETIME 5000 // Primary reading loop time (ms)

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

  int res = analogRead(VIN_APIN);
  return res * 0.0532; // Vbatt in volts
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
    DigiUSB.println(F("Begin"));
  #else
    dht.setup(DHT_PIN);
  #endif
  dht.setup(DHT_PIN);
  pinMode(VIN_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
}

/*   LOOP     */
#ifdef DEVEL
  int Ptemp=24;
  int Phumi=60;
  float Pbatt=12.5;
#endif

void loop() {
  #ifdef DEVEL
    DigiUSB.print(millis());
    DigiUSB.print(F(" : "));
  #endif

  // Readings
  #ifdef DEVEL
    int temp = Ptemp;
    int humi = Phumi;
    float batt = Pbatt;
  #else
    int temp = dht.getTemperature();
    int humi = dht.getHumidity();
    float batt = readVbatt();
  #endif

  if (strcmp(dht.getStatusString(),"OK") != 0) 
  {
    flashError();
    #ifdef DEVEL
      DigiUSB.print(F("Err : "));
    #endif
  }
  else 
  {
    // Flash out values when button pressed
    flashInt(temp);
    flashInt(humi);
    flashFloat(batt);
    
    #ifdef DEVEL
      DigiUSB.print(millis());
      DigiUSB.print(F(" : "));
      DigiUSB.print(temp);
      DigiUSB.print(F("C : "));
      DigiUSB.print(humi);
      DigiUSB.print(F("% : "));
      DigiUSB.print(int(batt*1000));
      DigiUSB.print(F("mV"));
      DigiUSB.println();
    #endif
  } 

  #ifdef DEVEL
    myDelay(4000);
  #else
    myDelay(60000); 
  #endif
}
