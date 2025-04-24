#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Indica se um programa está em execução.
 */
extern bool program_running;

/**
 * Posição atual no eixo Y para controle de menus.
 */
extern unsigned int pos_y;

/**
 * Índice da opção atualmente selecionada no menu.
 */
extern unsigned int opcao_atual;

/**
 * Lista de opções disponíveis no menu.
 */
extern const char *opcoes[];

/**
 * Total de opções disponíveis no menu.
 */
extern const unsigned int total_opcoes;

#endif // GLOBALS_H