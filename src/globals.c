#include "globals.h"

// Indica se o programa está em execução
bool program_running = false;

// Posição atual no eixo Y para controle de menus no display
unsigned int pos_y = 12;

// Índice da opção atualmente selecionada no menu
unsigned int opcao_atual = 0;

// Lista de opções disponíveis no menu (portas lógicas)
const char *opcoes[] = {"AND", "OR", "NOT", "NAND", "NOR", "XOR", "XNOR"};

// Total de opções disponíveis no menu
const unsigned int total_opcoes = 7;

// Guarda o valor da entrada A (inicia como true por padrão)
bool entrada_a = true;

// Guarda o valor da entrada B (inicia como true por padrão)
bool entrada_b = true;