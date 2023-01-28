/* ds18b20-t44.h - header file for ds18b20-serial project
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
 *           (serial out) PB0 -|2  13|- PA0
 *          (ds18b20 I/O) PB1 -|3  12|- PA1
 *                        PB3 -|4  11|- PA2
 *        (ds18b20 power) PB2 -|5  10|- PA3
 *                        PA7 -|6   9|- PA4
 *                        PA6 -|7   8|- PA5
 *                             |-----|
*/

#include "ds18b20-common.h"

/* ds18b20-serial port and pin selections for ATtiny44
*/
#define HZ					1000000
#define ASYNC_TX_PORT		'B'
#define ASYNC_TX_PIN		PB0
#define T1W_PORT			'B'
#define DS18B20_PIN			PB1
#define DS18B20_POWER_PORT	'B'
#define DS18B20_POWER_PIN	PB2

#endif
