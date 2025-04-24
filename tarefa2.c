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
    uint last_pos_y = pos_y;

    while (1) {
        atualiza_menu(&countdown, &countup, &last_pos_y);
        verifica_botao();
        sleep_ms(100);
    }

    return 0;
}
