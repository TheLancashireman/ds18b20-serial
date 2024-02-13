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
#include "ds18b20.h"
#include "tinylib.h"
#include "tinyio.h"
#include <avr/pgmspace.h>

/* Disable sections of the main loop for power measurements.
 * All have to be 1 for normal operation.
*/
#define DO_SLEEP	1
#define DO_MEASURE	1
#define DO_SENDTEMP	1

#if OPT_PULSECOUNT
#define DO_COUNT	1
#define DO_SENDCNT	1
#else
#define DO_COUNT	0
#define DO_SENDCNT	0
#endif

/* Use wdsleep(secs) if true; sleep(intervals) if false
*/
#define USE_WDSLEEP		1

#if USE_WDSLEEP
#define TCONV(x)		(x)
#define SLEEP(x)		wdsleep(DS18B20_SLEEP_MODE, x)
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

#if OPT_PULSECOUNT
static inline void counter_init(void)
{
	/* PA4 has to be an input with pullup
	*/
	port_pin_mode('A', PA4, PULLUP);	/* T1 input */

	TCCR1A = 0x00;		/* OCRA and OCRB disconnected, normal mode */
	TCCR1B = 0x06;		/* ICP not used, normal mode, external clock falling edge */
	TCCR1C = 0x00;		/* No forced compare */
	TCNT1 = 0;
						/* Don't care what OCR1A, OCR1B and ICR1 are */
	TIMSK1 = 0x00;		/* Mask all the interrupts */
	TIFR1 = 0x27;		/* Clear all interrupt flags */
}

static inline u16_t read_t1(void)
{
	volatile u8_t h1, h2, l;
//	u8_t s = disable();
	do {
		h1 = TCNT1H;
		l = TCNT1L;
		h2 = TCNT1H;
	} while ( h1 != h2 );
//	restore(s);

	return ((u16_t)h1) * 256 + l;
}
#endif

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
#if OPT_PULSECOUNT
	u16_t count = 0;
	u16_t diff;
#endif

	/* Power consumption reduction measures
	*/
	DIDR0 = DIDR0_VAL;	// Disable all unused data-in buffers
	ACSR = (1<<ACD);

	/* Initialise
	*/
	timing_init();
	async_init();
#if OPT_PULSECOUNT
	counter_init();
#endif

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

#if DO_COUNT
		temp = read_t1();
		diff = temp - count;
		count = temp;
#endif

#if DO_MEASURE
		temp = ds18b20_read_temp();
#endif

#if DO_SENDTEMP
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

#if DS18B20_CVT_TIME
		putc(' ');
		put_byte(cvt_iter);
#endif

		putc('\n');
#endif

#if DO_SENDCNT
		putc('C');
		put_byte(id);

		putc(' ');
		put_byte((u8_t)(count/256));
		put_byte((u8_t)count);

		putc(' ');
		put_byte((u8_t)(diff/256));
		put_byte((u8_t)diff);

		putc('\n');
#endif
	}

	return 0;
}
