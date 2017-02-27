/*
 * usuario.h
 *
 *  Created on: 21/02/2017
 *      Author: raffaello
 */

#ifndef SRC_USUARIO_H_
#define SRC_USUARIO_H_

#include <avr/io.h>
#include "at24c64/at24c64.h"

#define TIPO_REGISTRO_USUARIO 				0
#define TIPO_REGISTRO_ACESSO 				1

#define CONFIG_POSICAO_TIPO_REGISTRO 		0
#define CONFIG_POSICAO_REGISTRO_EXCLUIDO 	1

typedef struct {
	uint8_t config; //0b100000X0 //registro de usuario. O X indica excluido, 1 para excluido e 0 para ativo
	uint16_t matricula;
	uint16_t senha;
	uint16_t codigo; //endereco de memoria i2c eeprom ou numero da linha de arquivo txt no sdcard
} usuario_t;

typedef struct {
	uint8_t config; //0b100000X1 //registro de acesso. O X indica excluido, 1 para excluido e 0 para ativo
	uint8_t ano;
	uint8_t mes;
	uint8_t dia;
	uint8_t hora;
	uint8_t minuto;
	uint8_t segundo;
	uint16_t cod_usuario; //endereco de memoria i2c eeprom ou numero da linha de arquivo txt no sdcard
	uint16_t codigo;
} acesso_t;

#define NEXT_USUARIO ((sizeof(usuario_t) - sizeof(uint16_t)) / sizeof(uint8_t))
#define NEXT_REGISTRO_ACESSO ((sizeof(acesso_t) - sizeof(usuario_t) + sizeof(uint16_t)) / sizeof(uint8_t))

extern void (*usuario_listar_callback)(usuario_t *u);
extern void (*usuario_relatorio_acesso_callback)(acesso_t *a);

extern void usuario_adicionar(usuario_t *u);
extern void usuario_listar();
extern void usuario_editar(usuario_t *u);
extern void usuario_remover(usuario_t *u);

extern void usuario_relatorio_acesso(acesso_t *a);

#endif /* SRC_USUARIO_H_ */
