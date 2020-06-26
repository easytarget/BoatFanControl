 /* boat fan control

 Reads DHT11 Temperature and Humidity plus the battery Voltage
 It uses these values to set the PWM fan appropriately while supporting
 automatic and user triggered powersave and off modes 

         D5 - Reset pin
         D4 - N/C       (USB-)
  Digi   D3 - Button    (USB-)
  spark  D2 - Vin Sense
         D1 - DHT11     (Onboard LED)
         D0 - Fan PWM

 Notes: 
  DHT11 is pretty low accuracy and only returns whole integer results.
  See definitions below on how to calculate voltage trigger levels.

  The default PWM frequency is 500Hz; this can be audible on the fan.
  Running a DigiSpark at higher PWM frequency is (relatively) easy but
  does involve modifying the wiring.c header file (in the digispark board
  toolchain).
  See: https://digistump.com/wiki/digispark/tricks#how_to_increase_hardware_pwm_frequency

  In my case I had to edit ~/.arduino15/packages/digistump/hardware/avr/1.6.7/cores/tiny/wiring.c
  - this is on linux, on Windows this should be somewhere like:
  C:\Users\<MyUserName>\AppData\Local\Arduino15\packages\digistump\hardware\avr\1.6.7\cores\tiny

  I followed the guide and set MS_TIMER_TICK_EVERY_X_CYCLES to 1 and the PWM frequency was
  now very high (32KHz), but the millis() timer ran at half speed. Grrr, timer0 issues.

  A very easy fix turns out to be programming the DigiSpark at 16MHz (fixed)
  frequency instead of the default USB sycnched clock setting of 16.5MHz.
  Changing the board to 'Board -> Digistump AVR Boards -> Digispark (16MHz, no USB)'
  restored the millis() timer to correct operation while retaining the fast PWM.
  NB: This fix must be re-applied in the (unlikely) event of the DigiStump boards package being updated.

*/

// Run with faster cycles and with different voltage triggers on my testbench 
//#define BENCH

#include "DHT11.h"
DHT11 dht;

// Set/clear bit functions for sleeping the ADC
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


#define FAN_PIN 0
#define DHT_PIN 1
#define VIN_PIN 2
#define VIN_APIN 1 // digital pin 2 is also analog pin 1
#define BUTTON_PIN 3 

// Values
#define FAN_OFF    0
#define FAN_LOW   95
#define FAN_HIGH 255
#define LED_OFF    0
#define LED_LOW   10
#define LED_HIGH 255

// The ADC reading is multiplied by a scale factor = (5/1024)*11 = 0.05371 to get Volts
// The 0-5v ADC range returns a 10 bit reading of VIN via a 10k:1k resistor divider
// Value used here was double-checked by calibration.
// Use the following when calculating VIN_LOW & VIN_GOOD
// #define VOLTAGESCALE 0.0531

// Limits
#define VIN_LOW  222  // turn on only when above 11.8v (integer) = 11.8 / VOLTAGESCALE
#define VIN_GOOD 235  // run full when above 12.5v (integer) = 12.5 / VOLTAGESCALE
#define TEMP_TRIGGER 28   // turn fan on when above this temperature (integer: degrees C)
#define HUMI_TRIGGER 70   // turn fan on when above this humidity (integer; percentage)

// In high power mode the fan PWM rises from FAN_LOW by this value for each integer
//  above TEMP_TRIGGER or HUMI_TRIGGER respectively (until constrained by FAN_HIGH).
#define TEMP_RISE 40   // = (FAN_HIGH - FAN_LOW) / 4 (4C tempperature range)
#define HUMI_RISE 8    // = (FAN_HIGH - FAN_LOW) / 20 (20% humidity range)

// Primary reading loop time (ms) and auto-resume
#define CYCLETIME      20000  // 20s
#define RESUMETIME  10800000  // 3hrs

#ifdef BENCH  // apply some overrides for testing on the bench
  #undef VIN_LOW
  #define VIN_LOW        151    //  8v (bench PSU only goes to 12v ;-)
  #undef VIN_GOOD
  #define VIN_GOOD       188    // 10v
  #undef CYCLETIME
  #define CYCLETIME       3000  //  6s
  #undef RESUMETIME
  #define RESUMETIME    300000  //  15mins
#endif

// Last 5 readings are retained
byte t[5];
byte h[5];
unsigned int v[5];

// Sleep: need to set:
// sleep mode fan on
// sleep mode fan off
// sleep period
  // period:: 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,
  // 5=500ms, 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
// sleep count
int counter = 0; // counts watchdog events to trigger readings
bool button = false;  // set when button pressed


/* Led flashes */

void flashFast(byte flashes, byte pwm)
{
  pinMode(DHT_PIN, OUTPUT);
  for (byte i=0; i < flashes; i++) {
    analogWrite(DHT_PIN,pwm);
    delay(80);
    digitalWrite(DHT_PIN,LOW);
    delay(150);
  }
}

/* Sleep Functions */

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

void setup_pininterrupt() {
  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(PCINT3);
}

// Watchdog Interrupt Service 
ISR(WDT_vect) {
  counter++;
}

// Pin interrupt service
ISR(PCINT0_vect) {
  button=true;
}

/*   SETUP    */

void setup() 
{
  pinMode(VIN_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  dht.setup(DHT_PIN);

  // pre-populate the results
  do {
    flashFast(3,LED_HIGH);
    delay(250);
    pinMode(DHT_PIN, INPUT);  // set to input for dht readings
    delay(250);
    t[0] = constrain(dht.getTemperature(),0,40);
    h[0] = constrain(dht.getHumidity(),0,100);
    v[0] = constrain(analogRead(VIN_APIN),0,350);
  } while (strcmp(dht.getStatusString(),"OK") != 0);
  for (byte i=1; i < 5; i++) {  
    t[i] = t[0];
    h[i] = h[0];
    v[i] = v[0];
  }

  // Set up interrupts
  setup_watchdog(8);
  setup_pininterrupt();
}

/*   LOOP     */

// Power mode. Defaults to high, then cycles ->off->low->high etc with button
enum powerstates{off,low,high} power = high;

unsigned long lastRead = -CYCLETIME; // force an immediate read cycle
unsigned long lastButton = 0; // make like we just pressed the button
int index = 0;
byte fan = 0;
byte led = 255;

void loop() {
  button = false;
  
  cbi(ADCSRA,ADEN);   // switch ADC off while asleep

  while(millis() - lastRead < CYCLETIME) 
  {
    delay(100);
    if (!digitalRead(BUTTON_PIN))
    {
      delay(100);  // debounce
      if (!digitalRead(BUTTON_PIN))  // still active
      {  // hold until released
        while (!digitalRead(BUTTON_PIN)) delay(10);
        delay(100); // debounce again
        button = true;
        lastRead = millis() - CYCLETIME; // fast exit time loop
      }
    }
  }

  sbi(ADCSRA,ADEN);   // switch ADC back on
  
  // auto change from off->low->full power according to resume timer by simulating a button press
  if ((power != high) && (millis() - lastButton > RESUMETIME)) button = true;

  // Process button
  if (button) {
    switch (power)  // Change power modes
    {
      case off:  power = low; 
                 flashFast(4,LED_HIGH);
                 led = LED_LOW;
                 break;
      case low:  power = high; 
                 flashFast(6,LED_HIGH);
                 led = LED_HIGH;
                 break;
      case high: power = off;
                 flashFast(2,LED_HIGH);
                 led = LED_OFF; 
                 break;
    }
    lastButton = millis();
    delay(1000);
  }

  // Readings
  pinMode(DHT_PIN, INPUT);  // set to input for the dht readings
  delay(1); // let pin settle

  // take readings and constrain to sensible value range
  byte temp = constrain(dht.getTemperature(),0,40);
  byte humi = constrain(dht.getHumidity(),0,100);
  float volt = constrain(analogRead(VIN_APIN),100,350);
  if (strcmp(dht.getStatusString(),"OK") != 0) 
  {
    // Reading error; flash led 10 times
    flashFast(10,max(led,LED_LOW));
  } 
  else
  {
    // Good reading; save it
    index++;
    index%=5;
    t[index] = temp;
    h[index] = humi;
    v[index] = volt;
  }

  pinMode(DHT_PIN, OUTPUT); // flash led after reading
  analogWrite(DHT_PIN,led);
  delay(10);
  if (power == low) delay(100);
  if (power == high) delay(200);
  digitalWrite(DHT_PIN,LOW);

  lastRead = millis();

  // Averages
  unsigned int ttot=0, tmax=0, tmin=255;
  unsigned int htot=0, hmax=0, hmin=255;
  unsigned int vtot=0, vmax=0, vmin=65534;
  for (byte i=0; i < 5; i++)    // last 5 readings are retained
  {
    ttot+=t[i];                  // Calculate totals while
    if (t[i] < tmin) tmin=t[i];  //  noting the highest/lowest values
    if (t[i] > tmax) tmax=t[i];
    htot+=h[i];
    if (h[i] < hmin) hmin=h[i];
    if (h[i] > hmax) hmax=h[i];
    vtot+=v[i];
    if (v[i] < vmin) vmin=v[i];
    if (v[i] > vmax) vmax=v[i];
  }
  ttot = ttot - tmax - tmin;   // take off min and max values from the totals
  htot = htot - hmax - hmin;
  vtot = vtot - vmax - vmin;
  unsigned int tempAvg = round(float(ttot) / 3);  // then divide by 3 to get a de-peaked average.
  unsigned int humiAvg = round(float(htot) / 3);  // note: we force a floating point 
  unsigned int voltAvg = round(float(vtot) / 3);  //  calculation to make the rounding work
 
  // Process values and decide on fan settings
  if ((voltAvg < VIN_LOW) || (power == off))
  {
    // Low battery: turn off.
    fan = 0;
  }
  else if ((voltAvg < VIN_GOOD) || (power == low))
  {
    // Poor battery: set fan to low speed based on temp+humidity
    if ((tempAvg > TEMP_TRIGGER) || (humiAvg > HUMI_TRIGGER)) 
    {
      fan = FAN_LOW;
    } else {
      fan = FAN_OFF;
    }
  }
  else 
  {
    // Good battery: set fan proportionally above FAN_LOW based on temp+humidity
    // Constrain result to never exceed FAN_HIGH
    unsigned int fanT = 0;
    unsigned int fanH = 0;
    if (tempAvg >= TEMP_TRIGGER)
    {
      fanT = min(FAN_LOW + ((tempAvg - TEMP_TRIGGER) * TEMP_RISE),FAN_HIGH); 
    }
    if (humiAvg >= HUMI_TRIGGER) 
    {
      fanH = min(FAN_LOW + ((humiAvg - HUMI_TRIGGER) * HUMI_RISE),FAN_HIGH);
    }
    fan = max(fanT,fanH); 
  }

  // This is why we do all the above.. ;-)
  analogWrite(FAN_PIN,fan);

}
