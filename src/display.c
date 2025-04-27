#include "display.h"
#include <string.h>
#include "globals.h"

ssd1306_t disp; // Instância do display OLED

/**
 * Inicializa o display OLED configurando o I2C e limpando o display.
 */
void init_display() {
    i2c_init(I2C_PORT, 400 * 1000); // Configura I2C a 400 KHz

    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);

    gpio_pull_up(PINO_SCL);
    gpio_pull_up(PINO_SDA);

    disp.external_vcc = false;

    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);

    clear_display(); // Limpa o display
    print_texto((char *)opcoes[opcao_atual], 18, 3); // Exibe a opção inicial
}

/**
 * Limpa o conteúdo do display OLED.
 */
void clear_display() {
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
}

/**
 * Exibe texto centralizado no display OLED.
 * 
 * @param msg   Mensagem a ser exibida.
 * @param pos_y Posição Y no display.
 * @param scale Escala do texto.
 */
void print_texto(char *msg, uint pos_y, uint scale) {
    uint text_width = strlen(msg) * 6 * scale; // Calcula a largura do texto
    uint pos_x = (128 - text_width) / 2;      // Centraliza o texto no eixo X

    clear_display(); // Limpa o display antes de exibir o texto
    ssd1306_draw_string(&disp, pos_x, pos_y, scale, msg);
    ssd1306_show(&disp);
}
