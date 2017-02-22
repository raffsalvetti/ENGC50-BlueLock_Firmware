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

#define TIPO_REGISTRO_USUARIO 		0
#define TIPO_REGISTRO_ACESSO 		1

#define CONFIG_TIPO_REGISTRO 		0
#define CONFIG_REGISTRO_EXCLUIDO 	1

typedef struct {
	uint8_t config;
	uint16_t codigo; //endereco de memoria i2c eeprom ou numero da linha de arquivo txt no sdcard
	uint16_t matricula;
	uint16_t senha;
} usuario;

typedef struct {
	uint8_t config;
	uint16_t cod_usuario; //endereco de memoria i2c eeprom ou numero da linha de arquivo txt no sdcard
	uint8_t ano;
	uint8_t mes;
	uint8_t dia;
	uint8_t hora;
	uint8_t minuto;
	uint8_t segundo;
} acesso;

extern void (*usuario_listar_callback)(usuario *u);

extern void usuario_adicionar(usuario *u);
extern void usuario_listar();
extern void usuario_editar(usuario *u);
extern void usuario_remover(usuario *u);

extern void usuario_relatorio_acesso(acesso *a);

#endif /* SRC_USUARIO_H_ */
