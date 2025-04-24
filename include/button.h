#ifndef BUTTON_H
#define BUTTON_H

// Pinos dos botões
#define BUTTON_A 5    // GPIO conectado ao Botão A
#define BUTTON_B 6    // GPIO conectado ao Botão B

void button_init(); // Função para inicializar os botões
bool button_a_pressed(); // Função para verificar se o Botão A foi pressionado
bool button_b_pressed(); // Função para verificar se o Botão B foi pressionado
bool button_a_released(); // Função para verificar se o Botão A foi liberado
bool button_b_released(); // Função para verificar se o Botão B foi liberado

#endif // BUTTON_H