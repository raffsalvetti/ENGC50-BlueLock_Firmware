/*
 * ds1307.h
 *
 *  Created on: 17/02/2017
 *      Author: raffaello.salvetti
 *
 *  Com base no projeto http://davidegironi.blogspot.com.br/2013/12/a-ds1307-library-for-avr-atmega.html#.WKxDdFUrLtQ
 */

#ifndef DS1307_H
#define DS1307_H

#define DS1307_ADDR (0x68<<1) //datasheet

extern void ds1307_init();
extern uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
extern void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);

#endif

