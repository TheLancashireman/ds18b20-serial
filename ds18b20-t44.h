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

/* ds18b20-serial port and pin selections for ATtiny44
*/

#define ASYNC_TX_PORT	'B'
#define ASYNC_TX_PIN	PB0
#define T1W_PORT		'B'
#define DS18B20_PIN		PB1

/* Other options. ToDo: put in common header?
*/
#define ASYNC_BITRATE	9600
#define PASSIVE_TIME	1
#define INT_LOCK		0
#define HZ				1000000

#endif
