/* ds18b20-common.h - header file for ds18b20-serial project
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
#ifndef DS18B20_COMMON_H
#define DS18B20_COMMON_H	1

#define PASSIVE_TIME		1		/* No overflow counting, no time variables */
#define INT_LOCK			0		/* Runs with interrupts locked (except in special places) */

#define ASYNC_BITRATE		9600
#define ASYNC_TX_INVERT		1		/* Uses oc/od line driver */

#define DS18B20_CVT_DLY_FIRST	WDSLEEP_256ms
#define DS18B20_CVT_DLY_LOOP	WDSLEEP_16ms
#define DS18B20_CVT_DLY_LIM		16

#define DS18B20_CVT_TIME		1

#endif
