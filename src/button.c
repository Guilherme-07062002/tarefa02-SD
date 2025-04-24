#include "button.h"
#include "hardware/gpio.h" // Ensure this header is included for GPIO definitions
#include "globals.h"

/**
 * Inicializa os botões A e B.
 * Configura os pinos como entrada com pull-up interno.
 */
void button_init(){
    // Configuração do GPIO do Botão A como entrada com pull-up interno
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Configuração do GPIO do Botão B como entrada com pull-up interno
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}

/**
 * Verifica o estado dos botões A e B.
 * Atualiza as variáveis globais entrada_a e entrada_b de acordo com o estado dos botões.
 */
void verify_buttons() {
    if (gpio_get(BUTTON_A) == 0) {
        entrada_a = false; // Atualiza o valor da entrada A 
    } else {
        entrada_a = true; // Atualiza o valor da entrada A
    }

    if (gpio_get(BUTTON_B) == 0) {
        entrada_b = false; // Atualiza o valor da entrada B
    } else {
        entrada_b = true; // Atualiza o valor da entrada B
    }
}
