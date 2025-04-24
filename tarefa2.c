#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definições de pinos e módulos
#define I2C_PORT i2c1
#define PINO_SCL 14
#define PINO_SDA 15
#define SW 22
#define VRX 26
#define VRY 27
#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define GREEN_LED_PIN 11

// Configurações de PWM
#define DIVIDER_PWM 16.0
#define PERIOD 4096
#define PERIOD_LED_PWM 2000
#define LED_STEP 100

// Variáveis globais
ssd1306_t disp;
bool program_running = false;
uint pos_y = 12;

// Variáveis globais para controle de opções
uint opcao_atual = 0; // Índice da opção atual
const char *opcoes[] = {"Opcao 1", "Opcao 2", "Opcao 3"}; // Lista de opções
const uint total_opcoes = 3; // Total de opções

// Função para inicializar periféricos
void inicializa() {
    stdio_init_all();

    // Inicializa ADC para joystick
    adc_init();
    adc_gpio_init(VRX);
    adc_gpio_init(VRY);

    // Inicializa I2C e display OLED
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SCL);
    gpio_pull_up(PINO_SDA);
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);

    // Inicializa LEDs
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);

    // Inicializa botão do joystick
    gpio_init(SW);
    gpio_set_dir(SW, GPIO_IN);
    gpio_pull_up(SW);

    // Limpa display
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
}

// Função para exibir texto no display
void print_texto(char *msg, uint pos_x, uint pos_y, uint scale) {
    ssd1306_draw_string(&disp, pos_x, pos_y, scale, msg);
    ssd1306_show(&disp);
}

// Lê valores dos eixos do joystick
void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value) {
    adc_select_input(ADC_CHANNEL_0);
    sleep_us(2);
    *vrx_value = adc_read();

    adc_select_input(ADC_CHANNEL_1);
    sleep_us(2);
    *vry_value = adc_read();
}

// Atualiza posição do menu com base no joystick
void atualiza_menu(uint *countdown, uint *countup, uint *last_pos_y) {
    adc_select_input(ADC_CHANNEL_0);
    uint adc_y_raw = adc_read();
    const uint bar_width = 40;
    const uint adc_max = (1 << 12) - 1;
    uint bar_y_pos = adc_y_raw * bar_width / adc_max;

    if (bar_y_pos < 15 && *countdown < 2) {
        pos_y += 12;
        (*countdown)++;
        if (*countup > 0) (*countup)--;
    } else if (bar_y_pos > 25 && *countup < 2) {
        pos_y -= 12;
        (*countup)++;
        if (*countdown > 0) (*countdown)--;
    }

    if (pos_y != *last_pos_y && !program_running) {
        *last_pos_y = pos_y;
    }
}

// Atualiza a opção selecionada com base no movimento horizontal do joystick
void atualiza_opcoes(uint *countleft, uint *countright, uint *histerese) {
    uint16_t vrx_value, vry_value;
    joystick_read_axis(&vrx_value, &vry_value);

    const uint adc_max = (1 << 12) - 1;
    const uint limiar_esquerda = adc_max * 0.25; // Limiar para movimento à esquerda
    const uint limiar_direita = adc_max * 0.75; // Limiar para movimento à direita

    // Incrementa o contador de histerese
    if (*histerese < 5) {
        (*histerese)++;
        return; // Aguarda até que o contador de histerese atinja o limite
    }

    // Verifica movimento para a esquerda
    if (vrx_value < limiar_esquerda && *countleft == 0) {
        opcao_atual = (opcao_atual == 0) ? total_opcoes - 1 : opcao_atual - 1;
        *countleft = 1; // Marca que o movimento foi detectado
        *countright = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Verifica movimento para a direita
    else if (vrx_value > limiar_direita && *countright == 0) {
        opcao_atual = (opcao_atual + 1) % total_opcoes;
        *countright = 1; // Marca que o movimento foi detectado
        *countleft = 0; // Reseta o contador do lado oposto
        *histerese = 0; // Reseta o contador de histerese
    }
    // Reseta os contadores se o joystick estiver na posição neutra
    else if (vrx_value >= limiar_esquerda && vrx_value <= limiar_direita) {
        *countleft = 0;
        *countright = 0;
    }

    // Exibe a opção atual no display
    ssd1306_clear(&disp);
    print_texto((char *)opcoes[opcao_atual], 6, 18, 1.5);
}

// Verifica se o botão foi pressionado
void verifica_botao() {
    if (gpio_get(SW) == 0) {
        print_texto("Pressionou", 6, 18, 1.5);
        while (gpio_get(SW) == 0) {
            sleep_ms(10);
        }
    }
}

// Função principal
int main() {
    inicializa();

    uint countdown = 0;
    uint countup = 2;
    uint countleft = 0;
    uint countright = 0; // Inicializado como 0 para evitar comportamento inesperado
    uint last_pos_y = pos_y;
    uint histerese = 5; // Controle de histerese para suavizar mudanças rápidas

    while (1) {
        atualiza_menu(&countdown, &countup, &last_pos_y);
        atualiza_opcoes(&countleft, &countright, &histerese);
        verifica_botao();
        sleep_ms(100);
    }

    return 0;
}
