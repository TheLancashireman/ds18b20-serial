/* ds18b20-serial.c - a remote temperature sensor
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

/*
 *                             |--v--|
 *                    PB5/Rst -|1   8|- Vcc
 *          (ds18b20 I/O) PB3 -|2   7|- PB2
 *           (serial out) PB4 -|3   6|- PB1
 *                        Gnd -|4   5|- PB0/PCINT0
 *                             |-----|
*/

#include "ds18b20.h"
#include "tinylib.h"
#include "tinyio.h"
#include <avr/pgmspace.h>

/* Disable sections of the main loop for power measurements.
 * All have to be 1 for normal operation.
*/
#define DO_SLEEP	1
#define DO_MEASURE	1
#define DO_SEND		1


/* Use wdsleep(secs) if true; sleep(intervals) if false
*/
#define USE_WDSLEEP		1

#if USE_WDSLEEP
#define TCONV(x)		(x)
#define SLEEP(x)		wdsleep(x)
#else
#define TCONV(x)		((x) * INTERVALS_PER_SEC)
#define SLEEP(x)		sleep(x)
#endif

/* EEPROM addresses
*/
#define EEP_ID		0	/* Unit identification */
#define EEP_TSLEEP	1	/* Sleep duration (seconds) */

/* put_byte() - write a single byte to the serial output as 2 hex digits
*/
static void put_byte(u8_t b)
{
	putc(tohex(b >> 4));
	putc(tohex(b));
}

/* put_temp() - write a temperature to the serial output
*/
static void put_temp(u16_t temp)
{
	putc(' ');
	putc(tohex(temp >> 8));
	put_byte((u8_t)temp);
}

/* main() - this is where it happens :-)
 *
 * To do
 *	- get id from eeprom
 *	- some kind of checksum
*/
int main(void)
{
	disable();

	/* Disable the watchdog
	*/
	MCUSR = 0;		// Ensure WDRF is clear
	WDTCR = 0x10;	// Set WDCE, clear others (disables watchdog)

	u16_t temp;
	s16_t tmin = 32767;
	s16_t tmax = -32767;
	u8_t id = read_eeprom(EEP_ID);
	u8_t t_sleep = TCONV(read_eeprom(EEP_TSLEEP));

	/* Power consumption reduction measures
	*/
	DIDR0 = 0x37;	// Disable all data-in buffers except ADC3 ( = PB3 : 1-wire interface)
	ACSR = (1<<ACD);

	/* Initialise
	*/
	timing_init();
	async_init();

	/* Startup message
	*/
	putc('S');
	put_byte(id);
	putc('\n');

	for (;;)
	{
#if DO_SLEEP
		SLEEP(t_sleep);
#endif

#if DO_MEASURE
		temp = ds18b20_read_temp();
#endif

#if DO_SEND
		putc('T');
		put_byte(id);

		if ( (temp >> 8) == 0x80 )
		{
			/* Error: print error indicator
			*/
			putc(' ');
			putc('*');
			putc('*');
			putc(tohex(temp));
		}
		else
		{
			/* Good temperature: print temp and calculate max/min
			*/
			put_temp(temp);
			if ( tmax < (s16_t)temp )	tmax = (s16_t)temp;
			if ( tmin > (s16_t)temp )	tmin = (s16_t)temp;
		}
		/* Print max/min
		*/
		put_temp((u16_t)tmin);
		put_temp((u16_t)tmax);
		putc('\n');
#endif
	}

	return 0;
}
