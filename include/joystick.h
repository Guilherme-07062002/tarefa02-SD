#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include "pico/stdlib.h"

// Definições de pinos e ADC para o joystick
#define VRY 27 // Pino do eixo Y do joystick
#define ADC_CHANNEL_1 1 // Canal ADC para o eixo Y

#define SW 22 // Pino do botão do joystick

/**
 * Inicializa o joystick (configuração do ADC).
 */
void init_joystick();

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
void joystick_read_axis(uint16_t *vry_value, uint *countup, uint *countdown, uint *histerese);

#endif // JOYSTICK_H
