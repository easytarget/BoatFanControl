/******************************************************************
  DHT11 Temperature & Humidity Sensor library for Arduino.

  Features:
  - Support for DHT11 only
  - Very low memory footprint
  - Very small code

  http://www.github.com/markruys/arduino-DHT

  Written by Mark Ruys, mark@paracas.nl.
  Edited by Marcos Meli

  BSD license, check license.txt for more information.
  All text above must be included in any redistribution.

  Datasheets:
  - http://www.micro4you.com/files/sensor/DHT11.pdf

 ******************************************************************/

#include "DHT11.h"

void DHT11::setup(uint8_t pin)
{
  DHT11::pin = pin;
  DHT11::resetTimer(); // Make sure we do read the sensor in the next readSensor()

}

void DHT11::resetTimer()
{
  DHT11::lastReadTime = millis() - 3000;
}

float DHT11::getHumidity()
{
  readSensor();
  return humidity;
}

float DHT11::getTemperature()
{
  readSensor();
  return temperature;
}

#ifndef OPTIMIZE_SRAM_SIZE

const char* DHT11::getStatusString()
{
  switch ( error ) {
    case DHT11::ERROR_TIMEOUT:
      return "TIMEOUT";

    case DHT11::ERROR_CHECKSUM:
      return "CHECKSUM";

    default:
      return "OK";
  }
}

#else

// At the expense of 26 bytes of extra PROGMEM, we save 11 bytes of
// SRAM by using the following method:

prog_char P_OK[]       PROGMEM = "OK";
prog_char P_TIMEOUT[]  PROGMEM = "TIMEOUT";
prog_char P_CHECKSUM[] PROGMEM = "CHECKSUM";

const char *DHT11::getStatusString() {
  prog_char *c;
  switch ( error ) {
    case DHT11::ERROR_CHECKSUM:
      c = P_CHECKSUM; break;

    case DHT11::ERROR_TIMEOUT:
      c = P_TIMEOUT; break;

    default:
      c = P_OK; break;
  }

  static char buffer[9];
  strcpy_P(buffer, c);

  return buffer;
}

#endif

void DHT11::readSensor()
{
  // Make sure we don't poll the sensor too often
  // - Max sample rate DHT11 is 1 Hz   (duty cicle 1000 ms)

  unsigned long startTime = millis();
  if ( (unsigned long)(startTime - lastReadTime) < (999L) ) {
    return;
  }
  lastReadTime = startTime;

  temperature = NAN;
  humidity = NAN;

  // Request sample

  digitalWrite(pin, LOW); // Send start signal
  pinMode(pin, OUTPUT);
  
  delay(18);

  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // Switch bus to receive data

  // We're going to read 83 edges:
  // - First a FALLING, RISING, and FALLING edge for the start bit
  // - Then 40 bits: RISING and then a FALLING edge per bit
  // To keep our code simple, we accept any HIGH or LOW reading if it's max 85 usecs long

  word rawHumidity;
  word rawTemperature;
  word data;

  for ( int8_t i = -3 ; i < 2 * 40; i++ ) {
    byte age;
    startTime = micros();

    do {
      age = (unsigned long)(micros() - startTime);
      if ( age > 90 ) {
        error = ERROR_TIMEOUT;
        return;
      }
    }
    while ( digitalRead(pin) == (i & 1) ? HIGH : LOW );

    if ( i >= 0 && (i & 1) ) {
      // Now we are being fed our 40 bits
      data <<= 1;

      // A zero max 30 usecs, a one at least 68 usecs.
      if ( age > 30 ) {
        data |= 1; // we got a one
      }
    }

    switch ( i ) {
      case 31:
        rawHumidity = data;
        break;
      case 63:
        rawTemperature = data;
        data = 0;
        break;
    }
  }

  // Verify checksum

  if ( (byte)(((byte)rawHumidity) + (rawHumidity >> 8) + ((byte)rawTemperature) + (rawTemperature >> 8)) != data ) {
    error = ERROR_CHECKSUM;
    return;
  }

  // Store readings

  humidity = rawHumidity >> 8;
  temperature = rawTemperature >> 8;

  error = ERROR_NONE;
}
