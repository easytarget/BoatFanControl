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

// The ADC reading is multiplied by a scale factor = (5/1024)*11 = 0.05371 to get Volts
// The 0-5v ADC range returns a 10 bit reading of VIN via a 10k:1k resistor divider
// Value used here is was double-checked by calibration.
#define VOLTAGESCALE 0.0531

// Values
#define FAN_LOW   96
#define FAN_HIGH 255
#define LED_LOW   10
#define LED_HIGH 255

// Limits
#define VIN_LOW  11.8  // turn Off below this
#define VIN_GOOD 12.5  // run full above this
#define TEMP_MAX 28    // fan runs above this temperature
#define HUMI_MAX 75    // fan runs above this humidity

// Primary reading loop time (ms)
#ifdef DEVEL
  #define CYCLETIME  5000
#else
  #define CYCLETIME 10000
#endif

// Last 10 readings
byte t[10];
byte h[10];
unsigned int v[10];

// Debug values
#ifdef DEVEL
  byte Ptemp = 24;
  byte Phumi = 60;
  int Pvolt = 238;
#endif

void myDelay(unsigned long d) {
  #ifdef DEVEL
    DigiUSB.delay(d);
  #else
    delay(d);
  #endif
}

int readVIN() 
{
  // Take ADC reading
  return analogRead(VIN_APIN);
}

void flashFast(byte f,byte p)
{
  pinMode(DHT_PIN, OUTPUT);
  for (byte i=0; i < f; i++) {
    analogWrite(DHT_PIN,p);
    myDelay(100);
    digitalWrite(DHT_PIN,LOW);
    myDelay(100);
  }
}
  
/*   SETUP    */

void setup() {                
  pinMode(VIN_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  #ifdef DEVEL
    DigiUSB.begin();
  #else
    dht.setup(DHT_PIN);
  #endif

  // pre-populate the results
  #ifdef DEVEL
    for (byte i=0; i < 10; i++) {
      t[i] = Ptemp;
      h[i] = Phumi;
      v[i] = Pvolt;
    }
  #else
    do {
      myDelay(250);
      t[0] = constrain(dht.getTemperature(),0,40);
      h[0] = constrain(dht.getHumidity(),0,100);
      v[0] = constrain(readVIN(),0,350);
    } while (strcmp(dht.getStatusString(),"OK") != 0);
    for (byte i=1; i < 10; i++) {  
      t[i] = t[0];
      h[i] = h[0];
      v[i] = v[0];
    }
  #endif

  flashFast(3,LED_HIGH);
}

/*   LOOP     */

// Globals for the loop
int index = 0;
bool button = false;
enum powerstates{off,low,high} power = high;
byte fan = 0;
byte led = 255;

void loop() {
  unsigned long start = millis();
  #ifdef DEVEL
    DigiUSB.print(start);
  #endif

  // Process button
  if (button) {
    switch (power) {
      case off: power = low; flashFast(2,LED_HIGH); break;
      case low: power = high; flashFast(5,LED_HIGH); break;
      case high: power = off; flashFast(1,LED_HIGH); break;
    }
  }
  button=false;

  // Readings
  pinMode(DHT_PIN, INPUT);  // set to input for the dht readings
  #ifdef DEVEL
    index++;
    index%=10;
    t[index] = Ptemp;
    h[index] = Phumi;
    v[index] = Pvolt;
    myDelay(100);
  #else
    myDelay(300);
    byte temp = constrain(dht.getTemperature(),0,40);
    byte humi = constrain(dht.getHumidity(),0,100);
    float volt = constrain(readVIN(),0,350);
    if (strcmp(dht.getStatusString(),"OK") != 0) {
      flashFast(3,255); 
    } else {
      index++;
      index%=10;
      t[index] = temp;
      h[index] = humi;
      v[index] = volt;
    }
  #endif
  myDelay(500); // turn pin to HIGH and longer delay in full mode
  pinMode(DHT_PIN, OUTPUT); // onboard led off after reading
  digitalWrite(DHT_PIN,LOW);

  // process results (array)
  unsigned int tt=0;
  unsigned int tmax=0;
  unsigned int tmin=255;
  unsigned int ht=0;
  unsigned int hmax=0;
  unsigned int hmin=255;
  unsigned int vt=0;
  unsigned int vmax=0;
  unsigned int vmin=65534;
  for (byte i=0; i < 10; i++) {
    tt+=t[i];
    if (t[i] < tmin) tmin=t[i];
    if (t[i] > tmax) tmax=t[i];
    ht+=h[i];
    if (h[i] < hmin) hmin=h[i];
    if (h[i] > hmax) hmax=h[i];
    vt+=v[i];
    if (v[i] < vmin) vmin=v[i];
    if (v[i] > vmax) vmax=v[i];
  }
  tt = tt-tmax-tmin;   // take off one min and one max value from 10 reading total
  unsigned int tempAvg = ceil(tt/8);  // then divide by 8 to get a de-peaked average
  ht = ht-hmax-hmin;   // do the same for humidity readings
  unsigned int humiAvg = ceil(ht/8);
  vt = vt-vmax-vmin;   // do the same for humidity readings
  float voltAvg = vt * VOLTAGESCALE / 8;

  switch (power) {
    case off: fan = 0; led = 0; break;
    case low: fan = FAN_LOW; led = LED_LOW; break;
    case high: fan = FAN_HIGH; led = LED_HIGH; break;
  }
  
  #ifdef DEVEL
    DigiUSB.print(':');
    DigiUSB.print(index);
    DigiUSB.print(' ');
    
    DigiUSB.print(tempAvg);
    DigiUSB.print(',');
    DigiUSB.print(humiAvg);
    DigiUSB.print(',');
    DigiUSB.print(int(voltAvg));
    DigiUSB.print('.');
    DigiUSB.print(int(voltAvg*10)%10);
    DigiUSB.print(',');
    DigiUSB.print(int(fan));
    DigiUSB.print(',');
    DigiUSB.print(int(led));
  #else
    analogWrite(FAN_PIN,fan);
  #endif

  while(millis() - start < CYCLETIME) {
    myDelay(100);
    #ifdef DEVEL 
      while(DigiUSB.available()) {
        char s = DigiUSB.read();
        switch (s) {
          case 'T': Ptemp=min(Ptemp+1,40); break;
          case 't': Ptemp=max(Ptemp-1,0); break;
          case 'H': Phumi=min(Phumi+1,100); break;
          case 'h': Phumi=max(Phumi-1,0); break;
          case 'V': Pvolt=min(Pvolt+1,350); break;
          case 'v': Pvolt=max(Pvolt-1,0); break;
          case 'b': button = true; start = millis() - CYCLETIME; break;
        }
      }
    #else
      if (!digitalRead(BUTTON_PIN)) {
        if (button == false) {
          button = true;
          start = millis() - CYCLETIME;
        }
      }
    #endif
  }
  #ifdef DEVEL
    DigiUSB.println();
  #endif
}
