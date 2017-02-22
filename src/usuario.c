/*
 * usuario.c
 *
 *  Created on: 21/02/2017
 *      Author: raffaello
 */

#include "usuario.h"

uint16_t ultimo_endereco = 0x00;
uint8_t i, read;

static void buscar_ultimo_endereco() {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS; i++) {
		at24c64_read_address(i, &read);
		//buscar por registro livre
	}
}

void usuario_adicionar(usuario_t *u) {
	if(ultimo_endereco == 0x00)
		buscar_ultimo_endereco();

	u->codigo = ultimo_endereco;
	u->config = (1 << 8) | (TIPO_REGISTRO_USUARIO << CONFIG_TIPO_REGISTRO);
	at24c64_write_byte(ultimo_endereco++, u->config);
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula & 0xFF));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha & 0xFF));
}

void usuario_listar(usuario_t *u) {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS ; i++) {
		at24c64_read_address(i, &read);
		if(read & (TIPO_REGISTRO_USUARIO << CONFIG_TIPO_REGISTRO)) {
			if(read & (1 << CONFIG_REGISTRO_EXCLUIDO)) {
				//usuario excluido
				//se o usuario estiver marcado como excluido o registro eh pulado
				i += (sizeof(usuario_t) / sizeof(uint8_t));
			} else {
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
				usuario_listar_callback(u); //chamando funcao de evento
			}
		} else if (read & (TIPO_REGISTRO_ACESSO << CONFIG_TIPO_REGISTRO)) {
			i += (sizeof(acesso_t) / sizeof(uint8_t)); //calcular o tamanho de endereco para fim de estrutura
		} else {
			//fazer alguma coisa aqui?
		}
	}
}

void usuario_editar(usuario_t *u) {
	at24c64_write_byte(u->codigo + 4, (uint8_t)(u->senha >> 8));
	at24c64_write_byte(u->codigo + 5, (uint8_t)(u->senha & 0xFF));
}

void usuario_remover(usuario_t *u) {
	u->config |= 1 << CONFIG_REGISTRO_EXCLUIDO;
	at24c64_write_byte(u->codigo, u->config);
}

void usuario_registrar_acesso(acesso_t *a){
	if(ultimo_endereco == 0x00)
		buscar_ultimo_endereco();
	a->config = (1 << 8) | (TIPO_REGISTRO_ACESSO << CONFIG_TIPO_REGISTRO);
	a->
}

void usuario_relatorio_acesso(acesso_t *a){

}
