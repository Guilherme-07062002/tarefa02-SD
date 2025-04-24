#include "globals.h"

// Indica se um programa está em execução
bool program_running = false;

unsigned int pos_y = 12;

// Índice da opção atualmente selecionada no menu
unsigned int opcao_atual = 0;

// Lista de opções disponíveis no menu
const char *opcoes[] = {"Opcao 1", "Opcao 2", "Opcao 3"};

const unsigned int total_opcoes = 3;