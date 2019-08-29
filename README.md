# Humidity sensor and fan controller for a small boat
## By Owen.
![The Plan](./Docs/parts.jpg)
* DigiSpark Based
 * ATTiny 85
 * Has a onboard 5v regulator
 * 6 IO pins.. very little extra cruft
 * Somewhat tricky to flash/develop for, Lack of a uart is a total pain during debug.
* PWM fan control via a mosfet
* Battery voltage sensing for powersave and shutdown
* A button.. to allow on/off/quiet, etc.
* DHT11 Temperature and Humidity sensor
 * Not ideal, something more accurate would be prefered but this is what I have,
