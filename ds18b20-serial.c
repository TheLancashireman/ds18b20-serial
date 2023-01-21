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

/* puth() - convert a nibble to a single ASCII-hex character and write to the serial port
*/
static inline void puth(u8_t h)
{
	h = (h & 0x0f);
	if ( h > 9)
		putc(h - 10 + 'A');
	else
		putc(h + '0');
}

/* putt() - write a temperature to the serial output
*/
static inline void putt(u16_t temp)
{
	putc(' ');
	puth(temp >> 8);
	puth(temp >> 4);
	puth(temp);
}

/* sleep() - delay for a while
 *
 * Temporary implementation. Need:
 * 	- delay parameter
 *	- low-power sleep
*/
static inline void sleep(void)
{
	u8_t t = TCNT0;
	for ( u16_t i = 0; i < 48000; i++ )	/* 48000 * 104us ~= 5s */
	{
		t = bit_delay(t);
	}
}

/* main() - this is where it happens :-)
 *
 * To do
 *	- a less frivolous message
 *	- some kind of checksum
*/
int main(void)
{
	u16_t temp;
	s16_t tmin = 32767;
	s16_t tmax = -32767;

	disable();
	timing_init();
	async_init();

	puts_P(PSTR("Hello world!\n"));
	for (;;)
	{
		sleep();
		temp = ds18b20_read_temp();

		puts_P(PSTR("T01 "));
		if ( (temp >> 8) == 0x80 )
		{
			/* Error: print error indicator
			*/
			puts_P(PSTR(" **"));
			puth(temp);
		}
		else
		{
			/* Good temperature: print temp and calculate max/min
			*/
			putt(temp);
			if ( tmax < (s16_t)temp )	tmax = (s16_t)temp;
			if ( tmin > (s16_t)temp )	tmin = (s16_t)temp;
		}
		/* Print max/min
		*/
		putt((u16_t)tmin);
		putt((u16_t)tmax);
		putc('\n');
	}

	return 0;
}
