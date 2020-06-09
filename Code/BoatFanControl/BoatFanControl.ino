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
//#define DEVEL

/*-------------------------------*/

#ifdef DEVEL
  #include <DigiUSB.h>
#else
  #include <DHT11.h>
  DHT11 dht;
#endif

#define FAN_PIN 0
#define DHT_PIN 1
#define VIN_PIN 2
#define VIN_APIN 1 // digital pin 2 is also analog pin 1
#define BUTTON_PIN 3 

// Scale factor for ADC1 to volts
#define VOLTAGESCALE 0.0531
// Primary reading loop time (ms)
#ifdef DEVEL
  #define CYCLETIME  5000
#else
  #define CYCLETIME 60000
#endif

// Store results
unsigned int t[10];
unsigned int h[10];
unsigned int v[10];

void myDelay(unsigned long d) {
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
  return res * 0.0531; // Vbatt in volts
}

void flashFast(byte f)
{
  pinMode(DHT_PIN, OUTPUT);
  for (byte i; i < f; i++) {
    digitalWrite(DHT_PIN,HIGH);
    myDelay(100);
    digitalWrite(DHT_PIN,LOW);
    myDelay(100);
  }
}
  

/*   SETUP    */

void setup() {                
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  #ifdef DEVEL
    DigiUSB.begin();
    DigiUSB.println(F("Begin"));
    flashFast(10);
  #else
    flashFast(100);
    myDelay(1000);
    dht.setup(DHT_PIN);
  #endif

  // pre-populate the results
  int firstTemp = 22;
  int firstHumi = 55;
  int firstVolt = 12;
  #ifndef DEVEL
    do {
      myDelay(250);
      firstTemp = dht.getTemperature();
      firstHumi = dht.getHumidity();
      firstVolt = readVbatt();
    } while (strcmp(dht.getStatusString(),"OK") != 0);
  #endif
  for (int i;i<10;i++) {
    t[i] = firstTemp;
    h[i] = firstHumi;
    v[i] = firstVolt;
  }
  pinMode(VIN_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
}

/*   LOOP     */
#ifdef DEVEL
  int Ptemp=24;
  int Phumi=60;
  float Pbatt=12.5;
#endif

int index = 0;
void loop() {
  unsigned long start = millis();
  #ifdef DEVEL
    DigiUSB.print(start);
  #endif

  // Readings
  #ifdef DEVEL
    index++;
    index%=10;
    t[index] = Ptemp;
    h[index] = Phumi;
    v[index] = Pbatt;
  #else
    pinMode(DHT_PIN, INPUT);  // set to input for the dht readings
    myDelay(1000);      // let pin settle
    int temp = dht.getTemperature();
    int humi = dht.getHumidity();
    float batt = readVbatt();
    if (strcmp(dht.getStatusString(),"OK") != 0) {
      flashFast(10);
    } else {
      index++;
      index%=10;
      t[index] = temp;
      h[index] = humi;
      v[index] = batt;
    }
  #endif

  // process results (array)

  // Make decisions and set fan
  
  #ifdef DEVEL
    DigiUSB.print(F("ms : "));
    DigiUSB.print(index);
    DigiUSB.print(F("  : "));
    DigiUSB.print(t[index]);
    DigiUSB.print(F("C : "));
    DigiUSB.print(h[index]);
    DigiUSB.print(F("% : "));
    DigiUSB.print(int(v[index]*1000));
    DigiUSB.print(F("mV"));
    DigiUSB.println();
  #endif

  while(millis() - start < CYCLETIME) myDelay(100); // SLEEP/CHECK BUTTON HERE
}
