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
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "uart/uart.h"
#include "pfatfs/pff.h"
#include "ds1307/ds1307.h"
#include "at24c64/at24c64.h"
#include "usuario.h"

#define VERSION "1"

#define ACK_CHAR '!'

#define OK "OK"

#define UART_MAXREADTRY 50
#define UART_BAUD_RATE 9600

#define TIMER1_OCR1A 999

#define TIMER1_PRESCALER (1 << CS11)
#define TIMER_1MSTICKS 1 //timer ticks to count 1 msecond

char line[100];
char buf[10];

//void timer_init(void) {
//	TIMSK &= ~(1 << TOIE0); //timer 1 set at mode ctc, compare to oscr1a
//	OCR1A = TIMER1_OCR1A; //set value = fcpu / prescaler
//	TCCR1B |= (1 << WGM12); //mode 4, CTC on OCR1A
//	TIMSK |= (1 << OCIE1A); //interrupt on compare match
//	TCCR1B |= TIMER1_PRESCALER; // set prescaler
//	TIMSK |= (1 << TOIE0);
//}
//
///*
// * timer interrupt
// */
//ISR (TIMER1_COMPA_vect) {
//
//}

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

void usuario_listar_event(usuario_t *u) {
	memset(line, 0, sizeof(line)); //limpa string
	strcat(line, "cod:");
	itoa(u->codigo, buf, 10); strcat(line, buf);
	strcat(line, ";mat:");
	itoa(u->matricula, buf, 10); strcat(line, buf);
	strcat(line, ";sen:");
	itoa(u->senha, buf, 10); strcat(line, buf);
	strcat(line, "\r\n");
	uart_puts(line);
}

void usuario_relatorio_acesso_event(acesso_t *a){

}

int main(void) {
	DDRC = (1 << PC3);
	PORTC = (1 << PC3);

	uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;
	uint8_t rxc = 0;

	MCUSR = 0;
	wdt_disable();

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );
	sei();
	//timer_init();
	uart_puts("iniciando...\r\n");
	ds1307_init();
	//at24c64_init();

	usuario_listar_callback = &usuario_listar_event;
	usuario_relatorio_acesso_callback = &usuario_relatorio_acesso_event;

	wdt_enable(WDTO_1S); //reinicia o microcontrolador depois de 1s se o reset nao for acionado
	//ds1307_setdate(17, 02, 25, 00, 12, 00);
	while(1) {
		wdt_reset();//reinicia o watchdog
		//uart_puts("testando...\r\n");
		rxc = uart_getc();
		if (!(rxc & UART_NO_DATA) & !(rxc & UART_FRAME_ERROR) & !(rxc & UART_OVERRUN_ERROR) & !(rxc & UART_BUFFER_OVERFLOW)) {
			if(rxc == 's') { //set time
				uart_putc(ACK_CHAR); //ack byte
//				year = get_c();
//				month = get_c();
//				day = get_c();
//				hour = get_c();
//				minute = get_c();
//				second = get_c();
//				ds1307_setdate(year, month, day, hour, minute, second);
				ds1307_setdate(17, 02, 25, 00, 12, 00);
			} else if(rxc == 'g') { //get time
				uart_putc(ACK_CHAR); //ack byte
				ds1307_getdate(&year, &month, &day, &hour, &minute, &second);
				memset(line, 0, sizeof(line)); //limpa string
				itoa(day, buf, 10); strcat(line, buf);
				strcat(line, "/");
				itoa(month, buf, 10); strcat(line, buf);
				strcat(line, "/");
				itoa(year, buf, 10); strcat(line, buf);
				strcat(line, " ");
				itoa(hour, buf, 10); strcat(line, buf);
				strcat(line, ":");
				itoa(minute, buf, 10); strcat(line, buf);
				strcat(line, ":");
				itoa(second, buf, 10); strcat(line, buf);
				strcat(line, "\r\n");
				uart_puts(line);
			} else if(rxc == 'o') { //open lock
				uart_putc(ACK_CHAR); //ack byte
				PORTC |= (1 << PC3);
				uart_puts(OK);
			} else if(rxc == 'c') { //close lock
				uart_putc(ACK_CHAR); //ack byte
				PORTC &= ~(1 << PC3);
				uart_puts(OK);
			} else if(rxc == 'l') { //list users
				uart_putc(ACK_CHAR); //ack byte
				//wdt_disable(); //desarma o watchdog
				usuario_t u;
				usuario_listar(&u);
				//wdt_enable(WDTO_1S); //inicia o watchdog
				uart_puts(OK);
			} else if(rxc == 'a') { //add user
				uart_putc(ACK_CHAR); //ack byte
				usuario_t u;
				u.matricula = 6666;
				u.senha = 1234;
//				memset(line, 0, sizeof(line)); //limpa string
//				for(;;) {
//					buf[0] = get_c();
//					if(buf[0] == '#') break;
//					strcat(line, buf);
//				}
//				uart_puts(line);
				usuario_adicionar(&u);
				uart_puts(OK);
			} else if(rxc == 'd') { //del user
				uart_putc(ACK_CHAR); //ack byte

			} else if(rxc == 'e') { //edit user
				uart_putc(ACK_CHAR); //ack byte

			} else if(rxc == 'v') { //show version
				uart_putc(ACK_CHAR); //ack byte

			} else if(rxc == 't') { //teste
				uart_putc(ACK_CHAR); //ack byte
				memset(line, 0, sizeof(line)); //limpa string
				strcat(line, "uint8_t:");
				itoa(sizeof(uint8_t), buf, 10); strcat(line, buf);
				strcat(line, "\r\nuint16_t:");
				itoa(sizeof(uint16_t), buf, 10); strcat(line, buf);
				strcat(line, "\r\nchar:");
				itoa(sizeof(char), buf, 10); strcat(line, buf);
				strcat(line, "\r\nunsigned char:");
				itoa(sizeof(unsigned char), buf, 10); strcat(line, buf);
				strcat(line, "\r\nint:");
				itoa(sizeof(int), buf, 10); strcat(line, buf);
				strcat(line, "\r\nunsingned int:");
				itoa(sizeof(unsigned int), buf, 10); strcat(line, buf);
				uart_puts(line);
				uart_puts(OK);
			} else if(rxc == 'f') { //format memoria
				uart_putc(ACK_CHAR);
				wdt_disable(); //desarma o watchdog
				at24c64_format(); //operacao demora
				wdt_enable(WDTO_1S); //inicia o watchdog
				uart_puts(OK);
			} else if(rxc == 'w') { //format memoria

			} else if (rxc == 'r') {

			}
		}
		//_delay_ms(10);
	}

}
