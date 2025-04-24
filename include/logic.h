#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>

/**
 * Realiza a operação lógica AND.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação AND.
 */
bool logic_and(bool a, bool b);

/**
 * Realiza a operação lógica OR.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação OR.
 */
bool logic_or(bool a, bool b);

/**
 * Realiza a operação lógica XOR.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação XOR.
 */
bool logic_xor(bool a, bool b);

/**
 * Realiza a operação lógica NAND.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação NAND.
 */
bool logic_nand(bool a, bool b);

/**
 * Realiza a operação lógica NOR.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação NOR.
 */
bool logic_nor(bool a, bool b);

/**
 * Realiza a operação lógica XNOR.
 * 
 * @param a Entrada A.
 * @param b Entrada B.
 * @return Resultado da operação XNOR.
 */
bool logic_xnor(bool a, bool b);

/**
 * Realiza a operação lógica NOT.
 * 
 * @param a Entrada A.
 * @return Resultado da operação NOT.
 */
bool logic_not(bool a);

/**
 * Executa a operação lógica correspondente à opção selecionada.
 * Atualiza a variável entrada_a com o resultado da operação.
 */
void execute_logic_operation();

#endif // LOGIC_H
