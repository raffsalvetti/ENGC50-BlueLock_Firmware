/*
 * usuario.c
 *
 *  Created on: 21/02/2017
 *      Author: raffaello
 */

#include "usuario.h"

uint16_t ultimo_endereco = 0x00;
uint16_t i;
uint8_t read;

void (*usuario_listar_callback)(usuario_t *u);
void (*usuario_relatorio_acesso_callback)(acesso_t *a);

static void buscar_ultimo_endereco() {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS; i++) {
		at24c64_read_address(i, &read);
		if(read & ((1 << 7) | (TIPO_REGISTRO_USUARIO << CONFIG_POSICAO_TIPO_REGISTRO))) {
			i += NEXT_USUARIO;
		} else if(read & ((1 << 7) | (TIPO_REGISTRO_ACESSO << CONFIG_POSICAO_TIPO_REGISTRO))) {
			i += NEXT_REGISTRO_ACESSO;
		} else if (i == 0 && read == 0x00) {
			break;
		} else {
			ultimo_endereco = (i - 1); //subtrai o incremento
			break;
		}
	}
}

void usuario_adicionar(usuario_t *u) {
	if(ultimo_endereco == 0x00)
		buscar_ultimo_endereco();

	u->codigo = ultimo_endereco;
	u->config = ((1 << 7) | (TIPO_REGISTRO_USUARIO << CONFIG_POSICAO_TIPO_REGISTRO));
	at24c64_write_byte(ultimo_endereco++, u->config);
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->matricula & 0xFF));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(u->senha & 0xFF));
}

void usuario_listar(usuario_t *u) {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS ; i++) {
		at24c64_read_address(i, &read);
		if(read & ((1 << 7) | (TIPO_REGISTRO_USUARIO << CONFIG_POSICAO_TIPO_REGISTRO))) {
			if(read & (1 << CONFIG_POSICAO_REGISTRO_EXCLUIDO)) {
				//usuario excluido
				//se o usuario estiver marcado como excluido o registro eh pulado
				i += NEXT_USUARIO;
			} else {
				//usuario ativo
				u->codigo = i;
				u->config = read;
				at24c64_read_address(++i, &read);
				u->matricula = read << 8;
				at24c64_read_address(++i, &read);
				u->matricula |= (read & 0xFF);
				at24c64_read_address(++i, &read);
				u->senha = read << 8;
				at24c64_read_address(++i, &read);
				u->senha |= (read & 0xFF);
				(*usuario_listar_callback)(u); //chamando funcao de evento
			}
		} else if (read & ((1 << 7) | (TIPO_REGISTRO_ACESSO << CONFIG_POSICAO_TIPO_REGISTRO))) {
			//calcular o tamanho de endereco para fim de estrutura
			i += NEXT_REGISTRO_ACESSO;
		} else {
			//chegou ao fim dos registros validos
			break;
		}
	}
}

void usuario_editar(usuario_t *u) {
	at24c64_write_byte(u->codigo + 4, (uint8_t)(u->senha >> 8));
	at24c64_write_byte(u->codigo + 5, (uint8_t)(u->senha & 0xFF));
}

void usuario_remover(usuario_t *u) {
	u->config |= 1 << CONFIG_POSICAO_REGISTRO_EXCLUIDO;
	at24c64_write_byte(u->codigo, u->config);
}

void usuario_registrar_acesso(acesso_t *a){
	if(ultimo_endereco == 0x00)
		buscar_ultimo_endereco();
	a->config = ((1 << 7) | (TIPO_REGISTRO_ACESSO << CONFIG_POSICAO_TIPO_REGISTRO));
	at24c64_write_byte(ultimo_endereco++, a->config);
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(a->cod_usuario >> 8));
	at24c64_write_byte(ultimo_endereco++, (uint8_t)(a->cod_usuario));
	at24c64_write_byte(ultimo_endereco++, a->ano);
	at24c64_write_byte(ultimo_endereco++, a->mes);
	at24c64_write_byte(ultimo_endereco++, a->dia);
	at24c64_write_byte(ultimo_endereco++, a->hora);
	at24c64_write_byte(ultimo_endereco++, a->minuto);
	at24c64_write_byte(ultimo_endereco++, a->segundo);
}

void usuario_relatorio_acesso(acesso_t *a) {
	for(i = 0 ; i < AT24C64_MAX_ADDRESS ; i++) {
		at24c64_read_address(i, &read);
		if(read & (TIPO_REGISTRO_ACESSO << CONFIG_POSICAO_TIPO_REGISTRO)) {
			if(read & (1 << CONFIG_POSICAO_REGISTRO_EXCLUIDO)) {
				//registro de acesso excluido
				//se o registro de acesso estiver marcado como excluido o registro eh pulado
				i += NEXT_REGISTRO_ACESSO;
			} else {
				//registro de acesso ativo
				a->codigo = i;
				a->config = read;
				at24c64_read_address(++i, &read);
				a->cod_usuario = read << 8;
				at24c64_read_address(++i, &read);
				a->cod_usuario |= (read & 0xFF);
				at24c64_read_address(++i, &read);
				a->ano = read;
				at24c64_read_address(++i, &read);
				a->mes = read;
				at24c64_read_address(++i, &read);
				a->dia = read;
				at24c64_read_address(++i, &read);
				a->hora = read;
				at24c64_read_address(++i, &read);
				a->minuto = read;
				at24c64_read_address(++i, &read);
				a->segundo = read;
				(*usuario_relatorio_acesso_callback)(a);
			}
		} else if (read & (TIPO_REGISTRO_USUARIO << CONFIG_POSICAO_TIPO_REGISTRO)) {
			//calcular o tamanho de endereco para fim de estrutura
			i += NEXT_USUARIO;
		} else {
			//chegou ao fim dos registros validos
			break;
		}
	}
}
