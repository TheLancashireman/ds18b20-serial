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

## License

GPL v3 or later.  See the LICENSE file
