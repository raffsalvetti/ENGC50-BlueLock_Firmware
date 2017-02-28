/*
 * main.c
 *
 *  Created on: 14/02/2017
 *      Author: raffaello.salvetti
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "uart/uart.h"

#define VERSION "1"

#define ACK_CHAR '!'

#define OK "OK"

#define UART_MAXREADTRY 50
#define UART_BAUD_RATE 9600

#define TIMER1_OCR1A 999

#define TIMER1_PRESCALER (1 << CS11)
#define TIMER_1MSTICKS 1 //timer ticks to count 1 msecond

unsigned char get_ct(uint8_t gettry) {
	uint16_t rxc = uart_getc();
	if (!(rxc & UART_NO_DATA) & !(rxc & UART_FRAME_ERROR) & !(rxc & UART_OVERRUN_ERROR) & !(rxc & UART_BUFFER_OVERFLOW)) {
		return rxc;
	} else {
		if(gettry < UART_MAXREADTRY) {
			_delay_loop_1(0);
			return get_ct(gettry + 1);
		} else {
			return 0x00;
		}
	}
}
unsigned char get_c() {
	return get_ct(0);
}

void put_c(unsigned char c) {
	uart_putc(c);
}

int main(void) {
	DDRC = (1 << PC3);
	PORTC = (1 << PC3);

	uint8_t rxc = 0;

	MCUSR = 0;
	wdt_disable();

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );
	sei();
	uart_puts("iniciando...\r\n");

	wdt_enable(WDTO_1S); //reinicia o microcontrolador depois de 1s se o reset nao for acionado

	while(1) {
		wdt_reset();//reinicia o watchdog
		rxc = uart_getc();
		if (!(rxc & UART_NO_DATA) & !(rxc & UART_FRAME_ERROR) & !(rxc & UART_OVERRUN_ERROR) & !(rxc & UART_BUFFER_OVERFLOW)) {
			if(rxc == 'o') { //open lock
				uart_putc(ACK_CHAR); //ack byte
				PORTC |= (1 << PC3);
				uart_puts(OK);
			} else if(rxc == 'c') { //close lock
				uart_putc(ACK_CHAR); //ack byte
				PORTC &= ~(1 << PC3);
				uart_puts(OK);
			} else if(rxc == 's') {
				uart_putc(ACK_CHAR); //ack byte
				if(PORTC & (1 << PC3)) {
					uart_putc('c');
				} else {
					uart_putc('o');
				}
			} else if(rxc == 'v') { //show version
				uart_putc(ACK_CHAR); //ack byte

			}
		}
	}
}
