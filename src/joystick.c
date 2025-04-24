#include "joystick.h"
#include "hardware/adc.h" // Incluído para garantir o uso correto de adc_read
#include "globals.h"

/**
 * Inicializa o joystick (configuração do ADC).
 */
void init_joystick() {
    adc_init();
    adc_gpio_init(VRY); // Configura o pino do eixo Y para ADC

    // Inicializa botão do joystick
    gpio_init(SW);
    gpio_set_dir(SW, GPIO_IN);
    gpio_pull_up(SW);
}

/**
 * Lê o valor do eixo Y do joystick e atualiza a opção selecionada.
 * 
 * @param vry_value Ponteiro para armazenar o valor lido do eixo Y.
 * @param countup   Ponteiro para o contador de movimento para cima.
 * @param countdown Ponteiro para o contador de movimento para baixo.
 * @param histerese Ponteiro para o contador de histerese para suavizar mudanças rápidas.
 * 
 * A função realiza as seguintes operações:
 * - Lê o valor do eixo Y do joystick usando o ADC.
 * - Verifica se o joystick foi movido para cima ou para baixo com base em limiares predefinidos.
 * - Atualiza a variável global `opcao_atual` para refletir a opção selecionada.
 * - Utiliza um mecanismo de histerese para evitar mudanças rápidas e instáveis.
 */
void joystick_read_axis(uint16_t *vry_value, uint *countup, uint *countdown, uint *histerese) {
    adc_select_input(ADC_CHANNEL_1); // Seleciona o canal ADC para o eixo Y
    sleep_us(2); // Pequeno atraso para estabilizar a leitura
    *vry_value = adc_read(); // Lê o valor do ADC

    const uint adc_max = (1 << 12) - 1;
    const uint limiar_cima = adc_max * 0.25; // Limiar para movimento para cima
    const uint limiar_baixo = adc_max * 0.75; // Limiar para movimento para baixo

    // Incrementa o contador de histerese
    if (*histerese < 5) {
        (*histerese)++;
        return; // Aguarda até que o contador de histerese atinja o limite
    }

    // Verifica movimento para cima
    if (*vry_value < limiar_cima && *countup == 0) {
        opcao_atual = (opcao_atual == 0) ? total_opcoes - 1 : opcao_atual - 1;
        *countup = 1; // Marca que o movimento foi detectado
        *countdown = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Verifica movimento para baixo
    else if (*vry_value > limiar_baixo && *countdown == 0) {
        opcao_atual = (opcao_atual + 1) % total_opcoes;
        *countdown = 1; // Marca que o movimento foi detectado
        *countup = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Reseta os contadores se o joystick estiver na posição neutra
    else if (*vry_value >= limiar_cima && *vry_value <= limiar_baixo) {
        *countup = 0;
        *countdown = 0;
    }
}
