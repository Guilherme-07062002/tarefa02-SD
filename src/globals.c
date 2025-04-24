#include "globals.h"

// Indica se um programa está em execução
bool program_running = false;

unsigned int pos_y = 12;

// Índice da opção atualmente selecionada no menu
unsigned int opcao_atual = 0;

// Lista de opções disponíveis no menu
const char *opcoes[] = {"AND", "OR", "XOR", "NAND", "NOR", "XNOR"};

// Total de opções disponíveis no menu
const unsigned int total_opcoes = 6;

// Guarda valor da entrada A (Por padrão se inicia como true)
bool entrada_a = true;

// Guarda valor da entrada B
bool entrada_b = true;