/******************************************************************
  DHT11 Temperature & Humidity Sensor library for Arduino.

  Features:
  - Support for DHT11
  - Very low memory footprint
  - Very small code

  Written by Mark Ruys, mark@paracas.nl.
  Edited by Marcos Meli

  BSD license, check license.txt for more information.
  All text above must be included in any redistribution.

  Datasheets:
  - http://www.micro4you.com/files/sensor/DHT11.pdf

 ******************************************************************/

#ifndef dht_h
#define dht_h

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

class DHT11
{
public:

  typedef enum {
    ERROR_NONE = 0,
    ERROR_TIMEOUT,
    ERROR_CHECKSUM
  }
  DHT_ERROR_t;

  void setup(uint8_t pin);
  void resetTimer();

  float getTemperature();
  float getHumidity();

  DHT_ERROR_t getStatus() { return error; };
  const char* getStatusString();

  int getMinimumSamplingPeriod() { return 1000; }

  int8_t getLowerBoundTemperature() { return 0; };
  int8_t getUpperBoundTemperature() { return 50; };

  int8_t getLowerBoundHumidity() { return 20; };
  int8_t getUpperBoundHumidity() { return 90; };

  static float toFahrenheit(float fromCelcius) { return 1.8 * fromCelcius + 32.0; };
  static float toCelsius(float fromFahrenheit) { return (fromFahrenheit - 32.0) / 1.8; };

protected:
  void readSensor();

  float temperature;
  float humidity;

  uint8_t pin;

private:
  DHT_ERROR_t error;
  unsigned long lastReadTime;
};

#endif /*dht_h*/
