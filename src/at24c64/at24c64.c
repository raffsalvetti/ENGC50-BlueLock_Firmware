/*
 * at24c64.c
 *
 *  Created on: 17/02/2017
 *      Author: raffaello.salvetti
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../i2chw/i2cmaster.h"
#include "at24c64.h"

void at24c64_init() {
	i2c_init();
	_delay_us(10);
}

void at24c64_format() {
	uint8_t i = 0;
	for (i = 0; i < AT24C64_MAX_ADDRESS; i++) {
		at24c64_write_byte(i, 0x0);
	}
}

void at24c64_write_byte(uint16_t address, uint8_t byte) {
	i2c_start_wait(AT24C64_ADDR | I2C_WRITE);
	i2c_write((uint8_t)(address >> 8));
	i2c_write((uint8_t)(address & 0xFF));
	i2c_write(byte);
	i2c_stop();
}

void at24c64_read_address(uint16_t address, uint8_t *read) {
	i2c_start_wait(AT24C64_ADDR | I2C_WRITE);
	i2c_write((uint8_t)(address >> 8));
	i2c_write((uint8_t)(address & 0xFF));
	i2c_start_wait(AT24C64_ADDR | I2C_READ);
	*read = i2c_readNak();
	i2c_stop();
}

void at24c64_write_page(uint16_t address, const uint8_t *page) {
	i2c_start_wait(AT24C64_ADDR | I2C_WRITE);
	i2c_write((uint8_t)(address >> 8));
	i2c_write((uint8_t)(address & 0xFF));
	while (*page) {
		i2c_write(*page++);
	}
	i2c_stop();
}

void at24c64_read_sequential(uint16_t address, uint8_t *read) {
	uint8_t i = 0;
	i2c_start_wait(AT24C64_ADDR | I2C_WRITE);
	i2c_write((uint8_t)(address >> 8));
	i2c_write((uint8_t)address);
	i2c_start_wait(AT24C64_ADDR | I2C_READ);
	for (i = 0; i < AT24C64_SEQUANTIAL_READ_SIZE; i++) {
		read[AT24C64_SEQUANTIAL_READ_SIZE] = i2c_readAck();
	}
}

