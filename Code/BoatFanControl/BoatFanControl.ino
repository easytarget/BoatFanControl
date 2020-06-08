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

// For Sensor Debug use the fan pin to flash a LED for feedback
//#define FANDEBUG

/*-------------------------------*/

#ifdef DEVEL
  #include <DigiUSB.h>
#else
  #include <DHT11.h>
  DHT11 dht;
#endif

#define FAN_PIN 0
#define DHT_PIN 1
#define VCC_PIN 2
#define VCC_APIN 1 // digital pin 2 is also analog pin 1
#define BUTTON_PIN 3 

#define CYCLETIME 5000 // Primary reading loop time (ms)

#ifdef FANDEBUG
  // Defaults for flash sequences.
  const int flashOn = 150;   // On Duration
  const int flashOff = 200;  // Off Duration
  const int flashErr = 40;   // Error flash
  const int flashZero = 500; // long flash for zereo
  const int digitDelay = 1000; // delay between digits
  const int valueDelay = 3000; // delay after sending
#endif

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
  return res * 0.0532; // Vbatt in volts
}

void flashError(void)
{
  #ifdef FANDEBUG
    // Not a valid result.. v.rapid flash for a a few secs.
    for (int i = 0; i < 40; i++) 
    {
      analogWrite(FAN_PIN,255);
      myDelay(flashErr);
      analogWrite(FAN_PIN,0);
      myDelay(flashErr);
    }
    myDelay(valueDelay);
  #endif
}

void flashDigit(int digit)
{
  #ifdef FANDEBUG
    if (digit == 0) // long flash for a Zero
    {
      analogWrite(FAN_PIN,255);
      myDelay(flashZero);
      analogWrite(FAN_PIN,0);
      myDelay(flashOff);
    }
    else // N quick flashes for a value
    {
      for (int i = 0; i < digit; i++)
      {
        analogWrite(FAN_PIN,255);
        myDelay(flashOn);
        analogWrite(FAN_PIN,0);
        myDelay(flashOff);
      }
    }
  #endif
}

void flashInt(int val)
{
  #ifdef FANDEBUG
    // assumes val is an integer between 0 - 99 
    int valT = val / 10;
    int valU = val - (valT * 10);
    flashDigit(valT);
    myDelay(digitDelay);
    flashDigit(valU);
    myDelay(valueDelay);
  #endif
}

void flashFloat(int val)
{
  #ifdef FANDEBUG
    val = floor(val * 10);
    int valH = val / 100;  // this is crude, but works.
    int valT = (val - (valH * 100)) / 10;
    int valU = (val - (valH * 100) - (valT * 10));
    flashDigit(valH);
    myDelay(digitDelay);
    flashDigit(valT);
    myDelay(digitDelay);myDelay(digitDelay); // decimal position
    flashDigit(valU);
    myDelay(valueDelay);
  #endif
}

  

/*   SETUP    */

void setup() {                
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  #ifdef DEVEL
    DigiUSB.begin();
    DigiUSB.println(F("Hello"));
  #else
    dht.setup(DHT_PIN);
  #endif
  pinMode(VCC_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
}

/*   LOOP     */
#ifdef DEVEL
  int Ptemp=24;
  int Phumi=60;
  float Pbatt=12.5;
#endif

void loop() {
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

  #ifdef DEVEL
    if (1 == 0)
  #else
    if (strcmp(dht.getStatusString(),"OK") != 0) 
  #endif
  {
    flashError();
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
    #endif
  } 
  #ifdef DEVEL
    DigiUSB.println();
  #endif

  #ifdef DEVEL
    
  #else
    myDelay(60000); 
  #endif

}
