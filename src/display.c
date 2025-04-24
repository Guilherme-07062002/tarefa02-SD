#include "display.h"
#include <string.h>

ssd1306_t disp;

/**
 * Inicializa o display OLED.
 */
void init_display() {
    // Inicializa I2C
    i2c_init(I2C_PORT, 400 * 1000); // 400 KHz
    
    // Configura os pinos SCL e SDA
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);

    // Configura os pinos como saída
    gpio_pull_up(PINO_SCL);
    gpio_pull_up(PINO_SDA);

    // Configura o display OLED
    disp.external_vcc = false;

    // Aloca memória para o buffer do display
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);

    // Limpa o display OLED
    clear_display();
}

/**
 * Limpa o display OLED.
 */
void clear_display() {
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
}

/**
 * Exibe texto no display OLED centralizado.
 * 
 * @param msg   Mensagem a ser exibida.
 * @param pos_y Posição Y no display.
 * @param scale Escala do texto.
 */
void print_texto(char *msg, uint pos_y, uint scale) {
    // Calcula a largura do texto com base no tamanho da fonte e escala
    uint text_width = strlen(msg) * 6 * scale; // Cada caractere tem 6px de largura na fonte padrão
    uint pos_x = (128 - text_width) / 2;      // Centraliza o texto no eixo X

    clear_display(); // Limpa o display antes de exibir nova mensagem
    ssd1306_draw_string(&disp, pos_x, pos_y, scale, msg);
    ssd1306_show(&disp);
}
