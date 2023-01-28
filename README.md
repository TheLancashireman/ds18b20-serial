# ds18b20-serial remote temperature sensor

A remote temperature sensor module using a DS18B20 temperature sensor.

Transmit by wired asynchronous serial protocol.

## Hardware

* Attiny microcontroller (ATtiny13, ATtinyx5 or ATtinyx4, depending on build options)
* DS18B20 1-wire temperature sensor

Options:
* A 3.3v-capable USB-serial interface (e.g. FT232L board) for direct connection to PC
* A 3.3v-capable micro (e.g. STM32, RP2040) for data-logging

## Additional libraries

* tiny-bare-metal

## Note regarding DS19B20

My DS19B20 appears to be a fake. The standby power consumption is almost 50 uA when wired
for external power mode. It consumes more than 500 uA when wired for parasitic power.
The conversion time is well under the typical too: around 270 ms compared with a
typical 600 ms or so for a genuine part.

To overcome the power problem for a future wireless sensor, I changed my circuit to power
the DS18B20 from a pin on the ATtiny. The current draw during conversion is under 1.5 mA -
well within the capability of the 'tiny.


## License

GPL v3 or later.  See the LICENSE file
