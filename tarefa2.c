#include <stdio.h>
#include "pico/stdlib.h"

#include "globals.h"
#include "display.h"
#include "joystick.h"
#include "led.h"
#include "button.h"

// Função para inicializar periféricos
void inicializa() {
    stdio_init_all();

    // Inicializa o joystick
    init_joystick();

    // Inicializa I2C e display OLED
    init_display();

    // Inicializa LEDs
    init_leds();

    // Inicializa botões
    button_init();
}

// Atualiza a opção selecionada com base no movimento vertical do joystick
void atualiza_opcoes(uint *countup, uint *countdown, uint *histerese) {
    uint16_t vry_value;
    bool opcao_alterada = joystick_read_axis(&vry_value, countup, countdown, histerese);

    // Exibe a opção atual no display apenas se ela foi alterada
    if (opcao_alterada) {
        print_texto((char *)opcoes[opcao_atual], 18, 3); // Centralizado no display
    }

    // De acordo com a opção selecionada, realiza a ação correspondente
    verify_buttons(); // Verifica o estado dos botões
    switch (opcao_atual) {
        case 0: // AND
            // Implementar lógica para AND
            if (entrada_a && entrada_b) {
                green_led_on(); // Liga o LED verde se ambas as entradas forem verdadeiras
            } else {
                red_led_on(); // Liga o LED vermelho se qualquer entrada for falsa
            }
            break;
        case 1: // OR
            if (entrada_a || entrada_b) {
                green_led_on(); // Liga o LED verde se qualquer entrada for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se ambas as entradas forem falsas
            }
            break;
        case 2: // XOR
            if (entrada_a ^ entrada_b) {
                green_led_on(); // Liga o LED verde se apenas uma entrada for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se ambas forem verdadeiras ou ambas falsas
            }
            break;
        case 3: // NAND
            if (!(entrada_a && entrada_b)) {
                green_led_on(); // Liga o LED verde se não ambas as entradas forem verdadeiras
            } else {
                red_led_on(); // Liga o LED vermelho se ambas as entradas forem verdadeiras
            }
            break;
        case 4: // NOR
            if (!(entrada_a || entrada_b)) {
                green_led_on(); // Liga o LED verde se ambas as entradas forem falsas
            } else {
                red_led_on(); // Liga o LED vermelho se qualquer entrada for verdadeira
            }
            break;
        case 5: // XNOR
            if (!(entrada_a ^ entrada_b)) {
                green_led_on(); // Liga o LED verde se ambas as entradas forem iguais
            } else {
                red_led_on(); // Liga o LED vermelho se as entradas forem diferentes
            }
            break;
        default:
            break;
    }
}

// Função principal
int main() {
    inicializa();

    uint countup = 0;
    uint countdown = 0; // Inicializado como 0 para evitar comportamento inesperado
    uint histerese = 5; // Controle de histerese para suavizar mudanças rápidas

    while (1) {
        atualiza_opcoes(&countup, &countdown, &histerese);
        sleep_ms(100);
    }

    return 0;
}
