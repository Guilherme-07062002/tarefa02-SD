#include "joystick.h"
#include "hardware/adc.h" // Incluído para garantir o uso correto de adc_read

/**
 * Inicializa o joystick (configuração do ADC).
 */
void init_joystick() {
    adc_init();
    adc_gpio_init(VRY); // Configura o pino do eixo Y para ADC
}

/**
 * Lê o valor do eixo Y do joystick.
 * 
 * @param vry_value Ponteiro para armazenar o valor lido.
 */
void joystick_read_axis(uint16_t *vry_value) {
    adc_select_input(ADC_CHANNEL_1); // Seleciona o canal ADC para o eixo Y
    sleep_us(2); // Pequeno atraso para estabilizar a leitura
    *vry_value = adc_read(); // Lê o valor do ADC
}
