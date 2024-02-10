/* ds18b20-t44.h - header file for ds18b20-serial project
 *
 * This variant allows the use of a crystal to give better temperature stability
 * while supporting more sensors.
 *
 * It would be possible to support more sensors or use a crystal on the 8-pin devices,
 * but not both.
 *
 * (c) David Haworth
 *
 *  This file is part of ds18b20-serial.
 *
 *  ds18b20-serial is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ds18b20-serial is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ds18b20-serial.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DS18B20_T44_H
#define DS18B20_T44_H	1

/*
 *                             |--v--|
 *                        Vcc -|1  14|- Gnd
 *           (xtal 8 MHz) PB0 -|2  13|- PA0 (ds18b20 power)
 *           (xtal 8 MHz) PB1 -|3  12|- PA1 (ds18b20 I/O)
 *                  RST - PB3 -|4  11|- PA2
 *               (serial) PB2 -|5  10|- PA3
 *                        PA7 -|6   9|- PA4
 *                        PA6 -|7   8|- PA5
 *                             |-----|
*/

#include "ds18b20-common.h"

/* ds18b20-serial port and pin selections for ATtiny44
*/
#define HZ					1000000
#define ASYNC_TX_PORT		'B'
#define ASYNC_TX_PIN		PB2
#define T1W_PORT			'A'
#define DS18B20_PIN			PA1
#define DS18B20_POWER_PORT	'A'
#define DS18B20_POWER_PIN	PA0

/* Disable all data-in buffers except ADC1 ( = PA1 : 1-wire interface)
 *
 * Note: will probably have to enable the T0 or T1 buffer as well.
*/
#define DIDR0_VAL	0xfd

#endif
