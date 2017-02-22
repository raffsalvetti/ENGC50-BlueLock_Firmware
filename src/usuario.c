/*
 * usuario.c
 *
 *  Created on: 21/02/2017
 *      Author: raffaello
 */

#include "usuario.h"

uint16_t ultimo_endereco = 0x00;
uint8_t i, read;

void usuario_adicionar(usuario *u) {
	u->codigo = ultimo_endereco;
	u->config = TIPO_REGISTRO_USUARIO << CONFIG_TIPO_REGISTRO;
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula & 0xFF));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha & 0xFF));
}

void usuario_listar(usuario *u) {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS ; i++) {
		at24c64_read_address(i, &read);
		if(read & (TIPO_REGISTRO_USUARIO << CONFIG_TIPO_REGISTRO)) {
			u->codigo = i;
			u->config = read;
			at24c64_read_address(++i, &read);
			u->matricula = read << 8;
			at24c64_read_address(++i, &read);
			u->matricula |= read;
			at24c64_read_address(++i, &read);
			u->senha = read << 8;
			at24c64_read_address(++i, &read);
			u->senha |= read;
			usuario_listar_callback(u);//chamando funcao de evento
		} else if (read & (TIPO_REGISTRO_ACESSO << CONFIG_TIPO_REGISTRO)) {
			//calcular o tamanho de endereco para fim de estrutura
		} else {
			//fazer alguma coisa aqui?
		}
	}
}

void usuario_editar(usuario *u) {

}

void usuario_remover(usuario *u) {

}

void usuario_registrar_acesso(acesso *a){

}

void usuario_relatorio_acesso(acesso *a){

}
