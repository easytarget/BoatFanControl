# Humidity sensor and fan controller for a small boat
## By Owen.
#### My suffers from condensation, and a permanent fan will flatten the battery.

A Small controller based on a Digispark ATTiny controller I have lying around and a ispare DHT11 combined temperature and humidity sensor.
Turns the Fan on and Off (and several speeds in between) depending on the temperature, humidity, user input and battery state (voltage).

* DigiSpark Based
  * ATtiny85, plenty powerful enough for this application, and with a robust toolchain. It has 6 IO pins & very little extra cruft
  * Has a onboard 5v regulator, I can supply it with the battery voltage, and I can power the DHT11 from the 5v line
  * Somewhat tricky to flash/develop for, Lack of a uart is a total pain during debug since BitBang serial emulators eat half the memory+
* DHT11 Temperature and Humidity sensor
  * Not ideal, something more accurate would be prefered, but this is what I have.
  * A DHT22 would be an easy (plug and go) upgrade
* PWM fan control via a high-current logic-level NPN mosfet
  * I have a quiet but powerful (Noctuna) 12V PC case fan to run from this
* Battery voltage sensing for powersave and shutdown
* A button.. to allow on/off/quiet overrides

## Hardware

![Components](./Docs/parts-s.jpg)

![Ready To Fit](./Docs/encased-s.jpg)

Case design (scad) and model files are in the repo.

![Proud](./Docs/complete-s.jpg)

## Software
See the `BoatFanControl.ino` sketch in the `Software` folder. There are a number of other sketches in there that I used during development, you may find the \*Calibrate scripts useful to verify your sensors and voltage divider.

The DigiStump boards definitions are [here](http://digistump.com/package_digistump_index.json), this needs to be added to the Boards URL list in the preferences dialog of the IDE. The code is for the Arduino IDE, select `baoards -> Digistump AVR boards -> Digispark (16MHz, no USB)`. The No USB is advised to keep the clock stable when not plugged into a USB port.

Please read the notes at the top of the main sketch, by default the Digispark runs the fan at 500Hz, this is probably audible and might affect fan operation (the jury is out, I've seen people arguing both sides quite convincingly). In any case I decided to pump the fan PWM frequency up as high as possible. But this requires modifying a file in the Digispark boards folder. More details and URL's for sources are in the sketch header.

## Operation

* The controller takes a Temperature and Humidity reading every 20S and then decides how to set fan.
* Power Control; the controller also reads the battery voltage and uses this to reduce battery drain when needed.
  * Vmin->11.8V : Powersave; no activity, but still wake every 20s to take and process a voltage reading. 
  * 11.8->12.5V : Low Power; fan is restricted to 33% power
  * 12.5->Vmax  : Good Power; fan can rise to 100% power
* Fan Control
  * Is done on a simple Trigger value for temperature and humidity (28c and 70% respectively), the fan will start at 33% PWM power, and rise to 100% over the next four degrees temperature or 20% humidity. In low power mode the speed will never rise and remains at 30%
* User Control
  * The Button cycles: Full -> Quiet -> Off -> Full etc.. and flashes for feedback. two flashes for Off, four for Quiet and six for Full.
  * Quiet mode is basically the same as Low power mode.
  * After three hours the User mode will change to the next power level, the button works more like a 3 hour 'sleep' function, it is not a on/off switch.
* Average readings; I keep five readings and discard outliers before averaging the three middle values.
* Testing is tricky due to lack of resources, serial debug is not practical due to memory and pin limitations. I found it best to test the sensors uding the calibrate scripts provided. Then I ran on the testbench with much 'faster' reading and mode change cycles (there is a option for this in the #deines), and a PWM measuring (cycle and frequency) multimeter on the output. I then compared the results to an identical sensor running on a Arduino Uno running a standard Serial output DHT11 example, while breathing on sensors etc to trigger responses.

## Low Power
If the battery is good and the fan is running it will, obviously, use whatever current the fan takes (the mosfet is good to 5A). But once the voltage drops to powersave levels it is desirable to have the controller draw minimal power. l
* I use a low-power sleep mode between readings when the fan is off, this should reduce the load from the digispark from a few milliamps to a few microamps. I dont have a meter sensitive enough to measure this with any accuracy.
* If you are serious about reducing power I also suggest replacing the 10K/1K divider used for voltage sensing with a 100K/10K one
* The DHT11 draws up to 10 milliamp when doing a reading, but should be more like 100 microamps between readings (from specs and some websites that have measured this). If I do a MK2 pcb I will power the DHT11 from the unused D4 pin (the attiny can supply enough power for this) and switch it off between readings in software.
