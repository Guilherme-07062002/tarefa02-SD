#include "logic.h"
#include "globals.h"
#include "led.h"
#include "button.h"

bool logic_and(bool a, bool b) {
    return a && b;
}

bool logic_or(bool a, bool b) {
    return a || b;
}

bool logic_xor(bool a, bool b) {
    return a ^ b;
}

bool logic_nand(bool a, bool b) {
    return !(a && b);
}

bool logic_nor(bool a, bool b) {
    return !(a || b);
}

bool logic_xnor(bool a, bool b) {
    return !(a ^ b);
}

bool logic_not(bool a) {
    return !a;
}

void execute_logic_operation() {
    // Verifica o estado dos botões A e B, atualizando as variáveis globais entrada_a e entrada_b
    verify_buttons();

    // Executa a operação lógica correspondente a porta lógica selecionada e o estado dos botões
    switch (opcao_atual) {
        case 0: // AND
            if(logic_and(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação AND for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação AND for falsa
            }
            break;
        case 1: // OR
            if(logic_or(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação OR for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação OR for falsa
            }
            break;
        case 2: // NOT
            if(logic_not(entrada_a)) {
                green_led_on(); // Liga o LED verde se a operação NOT for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação NOT for falsa
            }
            break;
        case 3: // NAND
            if(logic_nand(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação NAND for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação NAND for falsa
            }
            break;
        case 4: // NOR
            if(logic_nor(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação NOR for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação NOR for falsa
            }
            break;
        case 5: // XOR
            if(logic_xor(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação XOR for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação XOR for falsa
            }
            break;
        case 6: // XNOR
            if(logic_xnor(entrada_a, entrada_b)) {
                green_led_on(); // Liga o LED verde se a operação XNOR for verdadeira
            } else {
                red_led_on(); // Liga o LED vermelho se a operação XNOR for falsa
            }
            break;
    }
}
