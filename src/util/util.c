/*
 * util.c
 *
 *  Created on: 21/02/2017
 *      Author: raffaello.salvetti
 */

#include <avr/io.h>
#include "util.h"

uint8_t util_bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

uint8_t util_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}
