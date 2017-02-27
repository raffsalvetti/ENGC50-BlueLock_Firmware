/*
 * ds1307.c
 *
 *  Created on: 17/02/2017
 *      Author: raffaello.salvetti
 *
 *  Com base no projeto http://davidegironi.blogspot.com.br/2013/12/a-ds1307-library-for-avr-atmega.html#.WKxDdFUrLtQ
 */

#include "avr/io.h"
#include "util/delay.h"
#include "avr/pgmspace.h"
#include "../i2chw/i2cmaster.h"
#include "../util/util.h"
#include "ds1307.h"


const uint8_t ds1307_qtd_dias_mes [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void ds1307_init() {
	i2c_init();
	_delay_us(10);
}

static uint16_t ds1307_date2days(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t days = d;
	for (uint8_t i = 1; i < m; ++i)
		days += pgm_read_byte(ds1307_qtd_dias_mes + i - 1);
	if (m > 2 && y % 4 == 0)
		++days;
	return days + 365 * y + (y + 3) / 4 - 1;
}

uint8_t ds1307_getdayofweek(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t day = ds1307_date2days(y, m, d);
	return (day + 6) % 7;
}

uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
	if (second < 0 || second > 59 ||
			minute < 0 || minute > 59 ||
			hour < 0 || hour > 23 ||
			day < 1 || day > 31 ||
			month < 1 || month > 12 ||
			year < 0 || year > 99)
		return 8;

	if(day > pgm_read_byte(ds1307_qtd_dias_mes + month - 1))
		return 0;

	uint8_t dayofweek = ds1307_getdayofweek(year, month, day);

	i2c_start_wait(DS1307_ADDR | I2C_WRITE);
	i2c_write(0x00);
	i2c_write(util_dec2bcd(second));
	i2c_write(util_dec2bcd(minute));
	i2c_write(util_dec2bcd(hour));
	i2c_write(util_dec2bcd(dayofweek));
	i2c_write(util_dec2bcd(day));
	i2c_write(util_dec2bcd(month));
	i2c_write(util_dec2bcd(year));
	i2c_write(0x00);
	i2c_stop();

	return 1;
}

void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second) {
	i2c_start_wait(DS1307_ADDR | I2C_WRITE);
	i2c_write(0x00);
	i2c_stop(); //nao funcionou na simulacao
	i2c_rep_start(DS1307_ADDR | I2C_READ);
	*second = util_bcd2dec(i2c_readAck() & 0x7F);
	*minute = util_bcd2dec(i2c_readAck());
	*hour = util_bcd2dec(i2c_readAck());
	i2c_readAck();
	*day = util_bcd2dec(i2c_readAck());
	*month = util_bcd2dec(i2c_readAck());
	*year = util_bcd2dec(i2c_readNak());
	i2c_stop();
}


