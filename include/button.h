#ifndef BUTTON_H
#define BUTTON_H

// Pinos dos botões
#define BUTTON_A 5    // GPIO conectado ao Botão A
#define BUTTON_B 6    // GPIO conectado ao Botão B

void button_init(); // Função para inicializar os botões
void verify_buttons(); // Função para verificar o estado dos botões

#endif // BUTTON_H