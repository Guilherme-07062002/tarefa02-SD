#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Pinos e módulo I2C
#define I2C_PORT i2c1
#define PINO_SCL 14
#define PINO_SDA 15

// Pino do botão do joystick
const int SW = 22;

// Pinos usados para ADC (joystick) e PWM
const int VRX = 26;          // Eixo X do joystick (ADC)
const int VRY = 27;          // Eixo Y do joystick (ADC)
const int ADC_CHANNEL_0 = 0; // Canal ADC para o eixo X
const int ADC_CHANNEL_1 = 1; // Canal ADC para o eixo Y

// LEDs RGB (usados tanto para controle digital quanto PWM)
const uint BLUE_LED_PIN  = 12;  // LED azul
const uint RED_LED_PIN   = 13;  // LED vermelho
const uint GREEN_LED_PIN = 11;  // LED verde

// Variáveis globais para o display e estado do programa
ssd1306_t disp; // Display OLED
bool program_running = false; // Indica se um programa está em execução

// Variáveis de controle do menu
uint pos_y = 12; // Variável de controle do menu

// Variáveis para controle do PWM
const float DIVIDER_PWM = 16.0; // Divisor do clock do PWM
const uint16_t PERIOD = 4096;   // Período do PWM
uint16_t led_b_level = 100;     // Nível inicial do LED azul
uint16_t led_r_level = 100;     // Nível inicial do LED vermelho
uint slice_led_b;               // Slice de PWM para o LED azul
uint slice_led_r;               // Slice de PWM para o LED vermelho

const uint16_t PERIOD_LED_PWM = 2000;   // Período do PWM (valor máximo do contador)
const uint16_t LED_STEP = 100;  // Passo de incremento/decremento para o duty cycle do LED
uint16_t led_level = 100;       // Nível inicial do PWM (duty cycle)

// Inicializa todos os periféricos
void inicializa() {
    stdio_init_all();

    // Inicializa e configura os pinos do joystick para ADC
    adc_init();
    adc_gpio_init(VRX);
    adc_gpio_init(VRY);

    // Inicializa o I2C e o display OLED
    i2c_init(I2C_PORT, 400 * 1000); // 400 KHz
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SCL);
    gpio_pull_up(PINO_SDA);
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);

    // Inicializa os LEDs (modo digital inicialmente)
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);

    // Inicializa o botão do joystick
    gpio_init(SW);
    gpio_set_dir(SW, GPIO_IN);
    gpio_pull_up(SW);

    // Limpa o display
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
}

/**
 * Função para escrever texto no display
 * 
 * @param msg   Mensagem a ser exibida
 * @param pos_x Posição X no display
 * @param pos_y Posição Y no display
 * @param scale Escala do texto
 */
void print_texto(char *msg, uint pos_x, uint pos_y, uint scale) {
    ssd1306_draw_string(&disp, pos_x, pos_y, scale, msg);
    ssd1306_show(&disp);
}

/**
 * Lê os valores dos eixos do joystick (X e Y)
 * 
 * @param vrx_value Ponteiro para armazenar o valor do eixo X
 * @param vry_value Ponteiro para armazenar o valor do eixo Y
 */
void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value) {
    // Seleciona o canal ADC para o eixo X e lê o valor
    adc_select_input(ADC_CHANNEL_0);
    sleep_us(2);
    *vrx_value = adc_read();

    // Seleciona o canal ADC para o eixo Y e lê o valor
    adc_select_input(ADC_CHANNEL_1);
    sleep_us(2);
    *vry_value = adc_read();
}

/**
 * Função principal
 * 
 * @return int Código de retorno
 */
int main() {
    inicializa();

    uint countdown = 0; // Para controle de histerese (movimento para baixo)
    uint countup = 2;   // Para controle de histerese (movimento para cima)
    uint last_pos_y = pos_y;

    while (1) {
        // Usa ADC (canal 0) para detectar o movimento do joystick no eixo Y
        adc_select_input(0);
        uint adc_y_raw = adc_read();
        const uint bar_width = 40;
        const uint adc_max = (1 << 12) - 1;
        uint bar_y_pos = adc_y_raw * bar_width / adc_max;

        // Ajusta a posição do seletor conforme a leitura do ADC
        if (bar_y_pos < 15 && countdown < 2) {
            pos_y += 12;
            countdown++;
            if (countup > 0) countup--;
        } else if (bar_y_pos > 25 && countup < 2) {
            pos_y -= 12;
            countup++;
            if (countdown > 0) countdown--;
        }

        // Atualiza o menu se a posição do seletor mudar e nenhum programa estiver em execução
        if (pos_y != last_pos_y && !program_running) {
            last_pos_y = pos_y;
        }

        sleep_ms(100);

        // Verifica se o botão foi pressionado
        if (gpio_get(SW) == 0) {
            print_texto("Pressionou", 6, 18, 1.5);
            
            // Aguarda liberação do botão para evitar múltiplas detecções
            while (gpio_get(SW) == 0) {
                sleep_ms(10);
            }
        }
    }
    return 0;
}
