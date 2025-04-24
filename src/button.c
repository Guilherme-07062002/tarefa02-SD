#include "button.h"
#include "hardware/gpio.h" // Ensure this header is included for GPIO definitions

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
 * Verifica se o Botão A foi pressionado.
 * Retorna verdadeiro se o botão A estiver pressionado, falso caso contrário.
 */
bool button_a_pressed() {
    return !gpio_get(BUTTON_A); // Retorna verdadeiro se o botão A estiver pressionado
}

/**
 * Verifica se o Botão B foi pressionado.
 * Retorna verdadeiro se o botão B estiver pressionado, falso caso contrário.
 */
bool button_b_pressed() {
    return !gpio_get(BUTTON_B); // Retorna verdadeiro se o botão B estiver pressionado
}

/**
 * Verifica se o Botão A foi liberado.
 * Retorna verdadeiro se o botão A estiver liberado, falso caso contrário.
 */
bool button_a_released() {
    return gpio_get(BUTTON_A); // Retorna verdadeiro se o botão A estiver liberado
}

/**
 * Verifica se o Botão B foi liberado.
 * Retorna verdadeiro se o botão B estiver liberado, falso caso contrário.
 */
bool button_b_released() {
    return gpio_get(BUTTON_B); // Retorna verdadeiro se o botão B estiver liberado
}