#include "led.h"
#include "hardware/gpio.h" // Inclui o cabeçalho para funções GPIO

/**
 * Inicializa os LEDs configurando os pinos como saída e desligando-os.
 */
void init_leds() {
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);

    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);
}

/**
 * Liga o LED vermelho e desliga o LED verde.
 */
void red_led_on() {
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(RED_LED_PIN, 1);
}

/**
 * Liga o LED verde e desliga o LED vermelho.
 */
void green_led_on() {
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 1);
}
