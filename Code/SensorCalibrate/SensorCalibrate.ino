#include <DigiUSB.h> // Remove at the end of days...
#include <DHT11.h>

// Some Hardware
#define DHT_PIN 1
#define LED_PIN 0

// Sensor
DHT11 dht;
// Store result
byte t[10];
byte h[10];

void setup() {                
  // initialize the IO pin
  pinMode(LED_PIN,OUTPUT);
  dht.setup(DHT_PIN);
}

void loop() {
  for (int i=0; i < 10; i++) {
    digitalWrite(LED_PIN,i%2);
    DigiUSB.delay(2000);
    t[i] = dht.getTemperature();
    h[i] = dht.getHumidity();
  }
  double t=0;
  int tmax=0;
  int tmin=255;
  double h=0;
  int hmax=0;
  int hmin=255;
  for (int i=0; i < 10; i++) {
    t+=t[i];
    if (t[i] < tmin) tmin=t[i];
    if (t[i] > tmax) tmax=t[i];
    h+=h[i];
    if (h[i] < hmin) hmin=h[i];
    if (h[i] > hmax) hmax=h[i];
  }
  t = t-tmax-tmin;
  double temp = h/8;
  h = h-hmax-hmin;
  double humi = h/8;

  for (int i=0;i<20;i++) {
    digitalWrite(LED_PIN,HIGH);
    DigiUSB.delay(50);
    digitalWrite(LED_PIN,LOW);
    DigiUSB.delay(50);
    }
  DigiUSB.begin();
  DigiUSB.delay(1000);
  DigiUSB.println(temp,4);
  DigiUSB.println(humi,4);
  DigiUSB.println();
}
