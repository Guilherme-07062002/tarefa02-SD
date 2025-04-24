#ifndef DISPLAY_H
#define DISPLAY_H

#include "hardware/i2c.h"
#include "ssd1306.h"

// Definições de pinos e módulo I2C
#define I2C_PORT i2c1
#define PINO_SCL 14
#define PINO_SDA 15

/**
 * Inicializa o display OLED.
 */
void init_display();

/**
 * Limpa o display OLED.
 */
void clear_display();

/**
 * Exibe texto no display OLED.
 * 
 * @param msg   Mensagem a ser exibida.
 * @param pos_x Posição X no display.
 * @param pos_y Posição Y no display.
 * @param scale Escala do texto.
 */
void print_texto(char *msg, uint pos_y, uint scale);

#endif // DISPLAY_H