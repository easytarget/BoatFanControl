// ShowSensorData
//
// Reads DHT11 temperature and humidity and Voltage on 
// the BoatFanController, and flashes a LED on the fan pin to
// show the readings

#include <DHT11.h>
DHT11 dht;

#define FAN_PIN 0
#define DHT_PIN 1
#define VCC_PIN 2
#define VCC_APIN 1 // digital pin 2 == Analog pin 1
#define BUTTON_PIN 3 

// Defaults for flash sequences.
const int flashOn = 150;
const int flashOff = 200;
const int flashErr = 40;
const int flashZero = 500; // long flash for zereo
const int digitDelay = 1000; // delay between digits
const int valueDelay = 2000; // delay after sending



float readVbatt() 
{
  // Take ADC reading and multiply by a scale factor = (5/1024)*11 = 0.05371
  // From: 0-5v ADC 10 bit reading, and 10k:1k resistor divider
  // Practical value used here is above + (tiny) calibration.

  int res = analogRead(VCC_APIN);
  return res * 0.053; // Vbatt in volts
}


void flashValue(int val)
// assumes val is an integer between 0 - 99 
{
  int valT = val / 10;
  int valU = val - (valT * 10);
  flashFan(valT);
  delay(digitDelay);
  flashFan(valU);
  delay(valueDelay);
}

void flashFan(int digit)
{
  if (digit == 0) // long flash for a Zero
  {
    analogWrite(FAN_PIN,255);
    delay(flashZero);
    analogWrite(FAN_PIN,0);
    delay(flashOff);
  }
  else // N quick flashes for a value
  {
    for (int i = 0; i < digit; i++)
    {
      analogWrite(FAN_PIN,255);
      delay(flashOn);
      analogWrite(FAN_PIN,0);
      delay(flashOff);
    }
  }
}

/*   SETUP    */

void setup() {                
  pinMode(FAN_PIN,OUTPUT);
  analogWrite(FAN_PIN,0);
  dht.setup(DHT_PIN);
  pinMode(VCC_PIN,INPUT);
  pinMode(BUTTON_PIN,INPUT);
}

/*   LOOP     */

void loop() {
  
  int temp = dht.getTemperature();
  int humi = dht.getHumidity();

  if (strcmp(dht.getStatusString(),"OK") != 0) 
  {
    // Not a valid result.. v.rapid flash for a a few secs.
    for (int i = 0; i < 40; i++) 
    {
      analogWrite(FAN_PIN,255);
      delay(flashErr);
      analogWrite(FAN_PIN,0);
      delay(flashErr);
    }
    delay(valueDelay);
  }
  else 
  {
    // Flash out values when button pressed

    // Temperature
    flashValue(temp);

    // Humidity
    flashValue(humi);
    
    // Voltage
    int vbatt = readVbatt() * 10;
    int vbattH = vbatt / 100;
    int vbattT = (vbatt - (vbattH * 100)) / 10;
    int vbattU = (vbatt - (vbattH * 100) - (vbattT * 10));
    flashFan(vbattH);
    delay(digitDelay);
    flashFan(vbattT);
    delay(digitDelay);delay(digitDelay); // decimal point
    flashFan(vbattU);
    delay(valueDelay);
  } 
 
  // wait for a button press
  while (digitalRead(BUTTON_PIN) == true) delay(10);
  while (digitalRead(BUTTON_PIN) == false) delay(10);
}
