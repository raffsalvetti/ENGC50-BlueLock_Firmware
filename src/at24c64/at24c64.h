/*
 * at24c64.h
 *
 *  Created on: 17/02/2017
 *      Author: raffaello.salvetti
 */

#ifndef AT24C64_H_
#define AT24C64_H_

#define AT24C64_SEQUANTIAL_READ_SIZE 10

#define AT24C64_ADDR (0x50 << 1) //endereco 1010000X (X eh read ou write)

extern void at24c64_init();
extern void at24c64_write_byte(uint16_t address, uint8_t byte);
extern void at24c64_write_page(uint16_t address, const uint8_t *page);
extern void at24c64_read_address(uint16_t address, uint8_t *read);
extern void at24c64_read_sequential(uint16_t address, uint8_t *read);

#endif /* AT24C64_H_ */
