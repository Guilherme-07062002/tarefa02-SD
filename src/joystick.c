#include "joystick.h"
#include "hardware/adc.h" // Inclui o cabeçalho para funções ADC
#include "globals.h"

/**
 * Inicializa o joystick configurando o ADC.
 */
void init_joystick() {
    adc_init();
    adc_gpio_init(VRY); // Configura o pino do eixo Y para ADC
}

/**
 * Lê o valor do eixo Y do joystick e atualiza a opção selecionada.
 * 
 * @param vry_value Ponteiro para armazenar o valor lido do eixo Y.
 * @param countup   Ponteiro para o contador de movimento para cima.
 * @param countdown Ponteiro para o contador de movimento para baixo.
 * @param histerese Ponteiro para o contador de histerese para suavizar mudanças rápidas.
 * 
 * @return true se a opção foi alterada, false caso contrário.
 */
bool joystick_read_axis(uint16_t *vry_value, uint *countup, uint *countdown, uint *histerese) {
    adc_select_input(ADC_CHANNEL_1); // Seleciona o canal ADC para o eixo Y
    sleep_us(2); // Pequeno atraso para estabilizar a leitura
    *vry_value = adc_read(); // Lê o valor do ADC

    const uint adc_max = (1 << 12) - 1;
    const uint limiar_cima = adc_max * 0.25; // Limiar para movimento para cima
    const uint limiar_baixo = adc_max * 0.75; // Limiar para movimento para baixo

    // Incrementa o contador de histerese
    if (*histerese < 5) {
        (*histerese)++;
        return false; // Aguarda até que o contador de histerese atinja o limite
    }

    // Verifica movimento para cima
    if (*vry_value < limiar_cima && *countup == 0) {
        opcao_atual = (opcao_atual == 0) ? total_opcoes - 1 : opcao_atual - 1;
        *countup = 1; // Marca que o movimento foi detectado
        *countdown = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
        return true; // Indica que a opção foi alterada
    }
    // Verifica movimento para baixo
    else if (*vry_value > limiar_baixo && *countdown == 0) {
        opcao_atual = (opcao_atual + 1) % total_opcoes;
        *countdown = 1; // Marca que o movimento foi detectado
        *countup = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
        return true; // Indica que a opção foi alterada
    }
    // Reseta os contadores se o joystick estiver na posição neutra
    else if (*vry_value >= limiar_cima && *vry_value <= limiar_baixo) {
        *countup = 0;
        *countdown = 0;
    }

    return false; // Nenhuma alteração foi feita
}
