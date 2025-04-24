#include "led.h"
#include "hardware/gpio.h" // Include the correct header for gpio functions

void init_leds() {
    // Inicializa LEDs
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);

    // Configura os pinos como saída
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Inicializa os LEDs como desligados
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);
}

void red_led_on() {
    gpio_put(GREEN_LED_PIN, 0); // Desliga o LED verde
    gpio_put(RED_LED_PIN, 1); // Liga o LED vermelho
}

void green_led_on() {
    gpio_put(RED_LED_PIN, 0); // Desliga o LED vermelho
    gpio_put(GREEN_LED_PIN, 1); // Liga o LED verde
}
