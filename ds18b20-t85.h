/* ds18b20-t85.h - header file for ds18b20-serial project
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
#ifndef DS18B20_T85_H
#define DS18B20_T85_H	1

/*
 *                             |--v--|
 *                    PB5/Rst -|1   8|- Vcc
 *          (ds18b20 I/O) PB3 -|2   7|- PB2 (ds18b20 power)
 *           (serial out) PB4 -|3   6|- PB1
 *                        Gnd -|4   5|- PB0/PCINT0
 *                             |-----|
*/

#include "ds18b20-common.h"

#if OPT_PULSECOUNT
#error "AtTiny85 doesn't have the required timer hardware for pulse counting"
#endif

/* ds18b20-serial port and pin selections for ATtiny85
*/
#define HZ					1000000
#define ASYNC_TX_PORT		'B'
#define ASYNC_TX_PIN		PB4
#define T1W_PORT			'B'
#define DS18B20_PIN			PB3
#define DS18B20_POWER_PORT	'B'
#define DS18B20_POWER_PIN	PB2

/* Disable all data-in buffers except ADC3 ( = PB3 : 1-wire interface)
*/
#define DIDR0_VAL	0x37

#endif
