#ifndef PONTO_H
#define PONTO_H

/*
 * @file ponto.h
 * @brief Interface para o módulo de Ponto.
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de pontos no plano cartesiano bidimensional.
 *
 * Um ponto é definido por um par de coordenadas (x, y) do tipo double.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação interna,
 * garantindo abstração e segurança no acesso aos dados.
 */

 /**
 * @brief Tipo abstrato que representa um ponto.
 */
typedef void* PONTO;

/**
 * @brief Cria e inicializa um novo ponto.
 *
 * @param x Coordenada x
 * @param y Coordenada y
 *
 * @return PONTO Ponteiro para o ponto criado
 * @return NULL Em caso de erro de alocação
 */
PONTO criarPonto(double x, double y);

/**
 * @brief Obtém as coordenadas de um ponto.
 *
 * @param p Ponto
 * @param x Saída: coordenada x
 * @param y Saída: coordenada y
 *
 * @note Os parâmetros x e y devem ser ponteiros válidos.
 */
void getPonto(PONTO p, double *x, double *y);

/**
 * @brief Libera a memória associada ao ponto.
 *
 * @param p Ponto
 *
 * @note Após a chamada, o ponto não deve mais ser utilizado.
 */
void killPonto(PONTO p);

#endif