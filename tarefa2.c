#include <stdio.h>
#include "pico/stdlib.h"

#include "globals.h"
#include "display.h"
#include "joystick.h"
#include "led.h"

// Função para inicializar periféricos
void inicializa() {
    stdio_init_all();

    // Inicializa o joystick
    init_joystick();

    // Inicializa I2C e display OLED
    init_display();

    // Inicializa LEDs
    init_leds();
}

// Atualiza a opção selecionada com base no movimento vertical do joystick
void atualiza_opcoes(uint *countup, uint *countdown, uint *histerese) {
    uint16_t vry_value;
    joystick_read_axis(&vry_value); // Usa a função do joystick para ler o eixo Y

    const uint adc_max = (1 << 12) - 1;
    const uint limiar_cima = adc_max * 0.25; // Limiar para movimento para cima
    const uint limiar_baixo = adc_max * 0.75; // Limiar para movimento para baixo

    // Incrementa o contador de histerese
    if (*histerese < 5) {
        (*histerese)++;
        return; // Aguarda até que o contador de histerese atinja o limite
    }

    // Verifica movimento para cima
    if (vry_value < limiar_cima && *countup == 0) {
        opcao_atual = (opcao_atual == 0) ? total_opcoes - 1 : opcao_atual - 1;
        *countup = 1; // Marca que o movimento foi detectado
        *countdown = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Verifica movimento para baixo
    else if (vry_value > limiar_baixo && *countdown == 0) {
        opcao_atual = (opcao_atual + 1) % total_opcoes;
        *countdown = 1; // Marca que o movimento foi detectado
        *countup = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Reseta os contadores se o joystick estiver na posição neutra
    else if (vry_value >= limiar_cima && vry_value <= limiar_baixo) {
        *countup = 0;
        *countdown = 0;
    }

    // Exibe a opção atual no display
    print_texto((char *)opcoes[opcao_atual], 6, 18, 1.5);
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
