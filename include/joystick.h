#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include "pico/stdlib.h"

// Definições de pinos e ADC para o joystick
#define VRY 27 // Pino do eixo Y do joystick
#define ADC_CHANNEL_1 1 // Canal ADC para o eixo Y

/**
 * Inicializa o joystick (configuração do ADC).
 */
void init_joystick();

/**
 * Lê o valor do eixo Y do joystick.
 * 
 * @param vry_value Ponteiro para armazenar o valor lido.
 */
void joystick_read_axis(uint16_t *vry_value);

#endif // JOYSTICK_H
