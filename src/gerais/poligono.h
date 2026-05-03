#ifndef POLIGONO_H
#define POLIGONO_H

#include "./estruturas/fila.h"

/*
 * @file poligono.h
 * @brief Interface para o módulo de Polígono.
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de polígonos. Um polígono é representado por um conjunto de vértices (coordenadas x, y),
 * armazenados em uma estrutura de fila.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação interna,
 * oferecendo operações para inserção e remoção de vértices, consulta de propriedades
 * (como número de vértices e bounding box), verificação de ponto interno, geração
 * de borda e hachura, além de gerenciamento de memória.
 */

/**
 * @brief Tipo abstrato que representa um polígono.
 */
typedef void* POLIGONO;

/**
 * @brief Cria e inicializa um novo polígono vazio.
 *
 * @return POLIGONO Ponteiro para o polígono criado
 * @return NULL Em caso de erro de alocação
 */
POLIGONO criarPoligono ();


/**
 * @brief Insere um novo vértice no polígono a partir de coordenadas.
 *
 * @param p Polígono
 * @param x Coordenada x
 * @param y Coordenada y
 *
 * @return int 1 se inserido com sucesso
 * @return int -1 em caso de erro
 */
int insertVertice_Poligono (POLIGONO p, double x, double y);

/**
 * @brief Remove o primeiro vértice inserido no polígono.
 *
 * @param p Polígono
 *
 * @return int 1 removido com sucesso
 * @return int -1 erro
 */
int removePrimeiroVertice_Poligono (POLIGONO p, double *x, double *y);

/**
 * @brief Retorna o número de vértices do polígono.
 *
 * @param p Polígono
 *
 * @return int Número de vértices
 * @return int -1 erro (p == NULL)
 */
int getNumeroVertices_Poligono (POLIGONO p);

/**
 * @brief Verifica se o polígono está vazio (não possui vertices).
 *
 * @param p Polígono
 *
 * @return int 1 vazio
 * @return int 0 não vazio
 * @return int -1 erro (p == NULL)
 */
int estaVazio_Poligono (POLIGONO p);

/**
 * @brief Calcula o bounding box do polígono.
 *
 * @param p Polígono
 * @param x Saída: coordenada x mínima
 * @param y Saída: coordenada y mínima
 * @param w Saída: largura
 * @param h Saída: altura
 *
 * @return int 1 sucesso
 * @return int -1 erro
 */
int getBoundingBox_Poligono (POLIGONO p, double *x, double *y, double *w, double *h);

/**
 * @brief Gera os segmentos da borda do polígono.
 *
 * @param p Polígono
 * @param f Fila de saída de segmentos
 *
 * @return int Quantidade de segmentos gerados
 * @return int -1 erro
 */
int produzBorda_Poligono (POLIGONO p, FILA f);
/**
 * @brief Gera hachura interna do polígono.
 *
 * @param p Polígono
 * @param distancia Espaçamento entre linhas
 * @param corp Cor de preenchimento
 * @param corb Cor da borda
 * @param f Fila de saída
 *
 * @return int 1 sucesso
 * @return int -1 erro
 */
int hachura_Poligono (POLIGONO p, double distancia, char* corp, FILA f);


/**
 * @brief Verifica se um ponto está dentro do polígono.
 *
 * @param p Polígono
 * @param x Coordenada x
 * @param y Coordenada y
 *
 * @return int 1 ponto dentro
 * @return int 0 ponto fora
 * @return int -1 erro (p == NULL)
 */
int isInside_Poligono (POLIGONO p, double x, double y);


void limparPoligono (POLIGONO p);

/**
 * @brief Libera a memória do polígono.
 *
 * @param p Polígono
 *
 * @return int 1 sucesso
 * @return int -1 erro
 */
int kill_Poligono (POLIGONO p);

#endif
